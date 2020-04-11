#include "../../extern/ProgressBar.hpp"
#include "Spike.h"

// logging
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
namespace logging = boost::log;

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

// program options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

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
      std::cout << "SPIKE FIRING RATE SIMULATION" << std::endl;
      std::cout << "-------------------------------" << std::endl;
      std::cout << "Calculates the firing rate of a "
                   "given neuron (that may be subject to an external signal)."
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
  BOOST_LOG_TRIVIAL(info) << "SPIKE FIRING RATE SIMULATION";

  // read parameters and construct classes
  BOOST_LOG_TRIVIAL(info) << "Reading parameters from input file " << input_file
                          << ".";
  pt::ptree root;
  pt::read_json(input_file, root);
  size_t N_neurons = (size_t)root.get<double>("Simulation.N_neurons");
  bool signal_given = root.get<bool>("Simulation.signal");

  // construct time frame, neuron and firing rate
  TimeFrame time_frame(input_file);
  auto neuron = NeuronFactory::create(input_file);
  auto firing_rate = FiringRateFactory::create(input_file, time_frame);

  // if signal is true in input file, construct signal
  std::unique_ptr<Signal> signal;
  if (signal_given) {
    signal = SignalFactory::create(input_file, time_frame);
  } else {
    signal = nullptr;
  }

  // progressbar
  ProgressBar progbar(N_neurons, 70);
  progbar.display();

  BOOST_LOG_TRIVIAL(info) << "Calculating firing rate.";
  // get spike trains
  if (!signal_given) {
#pragma omp parallel for
    for (size_t i = 0; i < N_neurons; i++) {
      SpikeTrain spike_train(time_frame.get_steps());
      neuron->get_spike_train(time_frame, spike_train);
      firing_rate->add_spike_train(spike_train);

#pragma omp critical
      ++progbar;
#pragma omp critical
      progbar.display();
    }
  } else {
#pragma omp parallel for
    for (size_t i = 0; i < N_neurons; i++) {
      SpikeTrain spike_train(time_frame.get_steps());
      neuron->get_spike_train(time_frame, *signal, spike_train);
      firing_rate->add_spike_train(spike_train);

#pragma omp critical
      ++progbar;
#pragma omp critical
      progbar.display();
    }
  }

  // calculate the firing rate
  firing_rate->calculate();

  BOOST_LOG_TRIVIAL(info) << "Finished calculation.";
  BOOST_LOG_TRIVIAL(info) << "Writing results to file.";

  // declare file for output
  std::ofstream file;
  file.open(opts.output_file);

  // write info to file
  file << "# SPIKE FIRING RATE SIMULATION\n"
       << "# -------------------------------\n"
       << "#\n";
  file << "# N_neurons = " << N_neurons << "\n";
  file << "#\n";
  neuron->print_info(file);
  file << "#\n";
  time_frame.print_info(file);
  file << "#\n";
  if (signal_given) {
    signal->print_info(file);
  }
  file << "#\n";
  file << "# Data format:\n"
       << "# Time, Firing rate\n";
  file << "#\n";

  // write firing rate values to file
  for (size_t i = 0; i < time_frame.get_steps(); i++) {
    file << time_frame.get_time(i) << "," << firing_rate->get_value(i) << "\n";
  }

  // close the file
  file.close();
  BOOST_LOG_TRIVIAL(info) << "Simulation finished.";
}