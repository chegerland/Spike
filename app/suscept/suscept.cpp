#include "../../extern/ProgressBar.hpp"
#include "Spike.h"

// logging
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

// program options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

namespace logging = boost::log;

void init_logger() {
  logging::core::get()->set_filter(logging::trivial::severity >=
                                   logging::trivial::info);
}

struct Parameters {
  std::string input_file;
  std::string output_file;
};

Parameters read_cmd(int argc, char *argv[]) {
  Parameters params = {"", ""};

  try {
    // List all options and their description
    po::options_description desc("Allowed options");
    desc.add_options()("help,h", "Show the help screen")(
        "file,f", po::value<std::string>(&(params.input_file)),
        "Path to input file (.json format)");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    // if the help option is given, show the flag description
    if (vm.count("help")) {
      std::cout << "SPIKE SUSCEPTIBILITY SIMULATION" << std::endl;
      std::cout << "-------------------------------" << std::endl;
      std::cout << "Calculates the linear and nonlinear susceptibility of a "
                   "given neuron."
                << std::endl;
      std::cout << "All parameters have to be defined in a .json input file."
                << std::endl;
      std::cout << std::endl;
      std::cout << desc << std::endl;
      exit(0);
    }

    if (vm.count("file")) {
      /* set according output file */
      params.output_file =
          params.input_file.substr(0, params.input_file.find_last_of('.')) +
          "_suscept.csv";
    } else {
      std::cerr << "No input file given!" << std::endl;
      std::cout << std::endl;
      std::cout << desc << std::endl;
      exit(-1);
    }

  } catch (std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
  }

  return params;
}

int main(int argc, char *argv[]) {

  // get file from command line
  Parameters opts;
  opts = read_cmd(argc, argv);
  std::string input_file = opts.input_file;

  // initialize logger
  init_logger();
  BOOST_LOG_TRIVIAL(info) << "SPIKE SUSCEPTIBILITY SIMULATION";

  // read parameters and construct classes
  BOOST_LOG_TRIVIAL(info) << "Reading parameters from input file " << input_file
                          << ".";

  pt::ptree root;
  pt::read_json(input_file, root);
  size_t N_neurons = (size_t)root.get<double>("Simulation.N_neurons");
  TimeFrame time_frame(input_file);
  auto neuron = NeuronFactory::create(input_file);

  // array for susceptibilities
  std::vector<std::complex<double>> suscept_lin;
  suscept_lin.resize(time_frame.get_steps() / 2 + 1);
  std::vector<std::complex<double>> suscept_nonlin;
  suscept_nonlin.resize(time_frame.get_steps() / 4 + 1);

  // initialize progressbar
  ProgressBar progbar(N_neurons, 70);
  progbar.display();

  BOOST_LOG_TRIVIAL(info) << "Calculating linear and nonlinear susceptibility.";
#pragma omp parallel for
  for (size_t i = 0; i < N_neurons; i++) {

    // array for susceptibility of single neuron
    std::vector<std::complex<double>> suscept_temp_lin;
    suscept_temp_lin.resize(time_frame.get_steps() / 2 + 1);

    std::vector<std::complex<double>> suscept_temp_nonlin;
    suscept_temp_nonlin.resize(time_frame.get_steps() / 4 + 1);

    // construct a new white noise signal, a spike train and a box firing rate
    WhiteNoiseSignal signal(input_file, time_frame);
    SpikeTrain spike_train(time_frame.get_steps());
    FiringRateBox firing_rate(time_frame);

    // get spike train
    neuron->get_spike_train(time_frame, signal, spike_train);
    firing_rate.add_spike_train(spike_train);

    // calculate firing rate
    firing_rate.calculate();

    // calculate susceptibility for this spike train
    susceptibility(signal.get_values(), firing_rate.get_values(), time_frame,
                   suscept_temp_lin);
    susceptibility_nonlinear_diag(signal.get_values(), firing_rate.get_values(),
                                  time_frame, suscept_temp_nonlin);

    // add susceptibility of the spike train to overall susceptibility
    for (size_t j = 0; j < time_frame.get_steps() / 4; j++) {
      suscept_lin[j] += 1. / ((double)N_neurons) * suscept_temp_lin[j];
      suscept_nonlin[j] += 1. / ((double)N_neurons) * suscept_temp_nonlin[j];
    }

    // only one thread at a time shall increase the progress counter
#pragma omp critical
    ++progbar;
#pragma omp critical
    progbar.display();
  }
  progbar.done();

  BOOST_LOG_TRIVIAL(info) << "Finished calculation.";
  BOOST_LOG_TRIVIAL(info) << "Writing results to file.";

  // construct another white noise to get info about its parameters (quite
  // inelegant isn't it?)
  WhiteNoiseSignal signal(input_file, time_frame);

  // write susceptibility to file
  std::ofstream file;
  file.open(opts.output_file);

  file << "# SPIKE SUSCEPTIBILITY SIMULATION\n"
       << "# -------------------------------\n"
       << "#\n";
  file << "# N_neurons = " << N_neurons << "\n";
  file << "#\n";
  neuron->print_info(file);
  file << "#\n";
  time_frame.print_info(file);
  file << "#\n";
  signal.print_info(file);
  file << "#\n";
  file << "# Data format:\n"
       << "# Frequency, Re(Suscept_1), Im(Suscept_1), Re(Suscept_2), "
          "Im(Suscept_2)\n";
  file << "#\n";

  for (size_t i = 0; i < time_frame.get_steps() / 4; i++) {
    file << (double)i / (time_frame.get_t_end() - time_frame.get_t_0()) << ","
         << std::real(suscept_lin[i]) << "," << std::imag(suscept_lin[i]) << ","
         << std::real(suscept_nonlin[i]) << "," << std::imag(suscept_nonlin[i])
         << "\n";
  }

  file.close();
  BOOST_LOG_TRIVIAL(info) << "Simulation finished.";
}