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

#include <mpi.h>

void master(const std::string &input_file, const std::string &output_file);
void minion(const std::string &input_file);

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

  // initialize mpi
  MPI_Init(&argc, &argv);

  // get world rank and size
  int world_rank, world_size;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // read command line options
  Parameters opts;
  opts = read_cmd(argc, argv);
  std::string input_file = opts.input_file;

  if (world_rank == 0)
    master(opts.input_file, opts.output_file);
  else
    minion(opts.input_file);

  // finalize mpi
  MPI_Finalize();

  return 0;
}

void master(const std::string &input_file, const std::string &output_file) {

  // initialize logger
  init_logger();
  BOOST_LOG_TRIVIAL(info) << "SPIKE SUSCEPTIBILITY SIMULATION";

  // read parameters and construct classes
  BOOST_LOG_TRIVIAL(info) << "Reading parameters from input file " << input_file
                          << ".";

  // read number of neurons
  pt::ptree root;
  pt::read_json(input_file, root);
  int N_neurons = (int)root.get<double>("Simulation.N_neurons");

  // get the world size
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // determine number of trials each process should handle
  // exclude master process
  int trials = N_neurons / world_size;

  BOOST_LOG_TRIVIAL(info) << "Sending " << trials << " trials to "
                          << world_size - 1 << " processes.";
  // send number of trials to each process and if signal is given
  for (int i = 0; i < world_size - 1; i++) {
    MPI_Send(&trials, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
  }

  // construct time frame and neuron
  TimeFrame time_frame(input_file);
  auto neuron = NeuronFactory::create(input_file);

  // array for susceptibilities
  std::vector<std::complex<double>> suscept_lin;
  suscept_lin.resize(time_frame.get_steps() / 4 + 1);
  std::vector<std::complex<double>> suscept_nonlin;
  suscept_nonlin.resize(time_frame.get_steps() / 4 + 1);

  BOOST_LOG_TRIVIAL(info) << "Calculating linear and nonlinear susceptibility.";
  for (int i = 0; i < trials; i++) {

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
      suscept_lin[j] += suscept_temp_lin[j];
      suscept_nonlin[j] += suscept_temp_nonlin[j];
    }
  }

  int length = time_frame.get_steps() / 4;

  // normalize susceptibility
  for (size_t j = 0; j < length; j++) {
    suscept_lin[j] = 1. / ((double)N_neurons) * suscept_lin[j];
    suscept_nonlin[j] = 1. / ((double)N_neurons) * suscept_nonlin[j];
  }

  BOOST_LOG_TRIVIAL(info) << "Finished calculation.";

  BOOST_LOG_TRIVIAL(info) << "Receiving values from subprocesses.";
  // receive arrays back from subprocesses
  std::vector<double> tmp_suscept_lin_real;
  std::vector<double> tmp_suscept_lin_imag;
  std::vector<double> tmp_suscept_nonlin_real;
  std::vector<double> tmp_suscept_nonlin_imag;
  tmp_suscept_lin_real.resize(length);
  tmp_suscept_lin_imag.resize(length);
  tmp_suscept_nonlin_real.resize(length);
  tmp_suscept_nonlin_imag.resize(length);

  std::complex<double> I(0., 1.);

  MPI_Status status;
  for (int i = 0; i < world_size - 1; i++) {

    // receive arrays
    MPI_Recv(tmp_suscept_lin_real.data(), length, MPI_DOUBLE, MPI_ANY_SOURCE, 0,
             MPI_COMM_WORLD, &status);
    MPI_Recv(tmp_suscept_lin_imag.data(), length, MPI_DOUBLE, MPI_ANY_SOURCE, 0,
             MPI_COMM_WORLD, &status);
    MPI_Recv(tmp_suscept_nonlin_real.data(), length, MPI_DOUBLE, MPI_ANY_SOURCE,
             0, MPI_COMM_WORLD, &status);
    MPI_Recv(tmp_suscept_nonlin_imag.data(), length, MPI_DOUBLE, MPI_ANY_SOURCE,
             0, MPI_COMM_WORLD, &status);

    // add array to overall firing rate
    for (int j = 0; j < length; j++) {
      suscept_lin[j] += 1. / ((double)N_neurons) *
                        (tmp_suscept_lin_real[j] + I * tmp_suscept_lin_imag[j]);
      suscept_nonlin[j] +=
          1. / ((double)N_neurons) *
          (tmp_suscept_nonlin_real[j] + I * tmp_suscept_nonlin_imag[j]);
    }
  }

  // construct another white noise to get info about its parameters (quite
  // inelegant isn't it?)
  WhiteNoiseSignal signal(input_file, time_frame);

  // write susceptibility to file
  std::ofstream file;
  file.open(output_file);

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

  for (int i = 0; i < length; i++) {
    file << (double)i / (time_frame.get_t_end() - time_frame.get_t_0()) << ","
         << std::real(suscept_lin[i]) << "," << std::imag(suscept_lin[i]) << ","
         << std::real(suscept_nonlin[i]) << "," << std::imag(suscept_nonlin[i])
         << "\n";
  }

  file.close();
  BOOST_LOG_TRIVIAL(info) << "Simulation finished.";
}

void minion(const std::string &input_file) {

  int trials;
  MPI_Status status;
  MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

  // construct time frame and neuron
  TimeFrame time_frame(input_file);
  auto neuron = NeuronFactory::create(input_file);

  // array for susceptibilities
  std::vector<std::complex<double>> suscept_lin;
  suscept_lin.resize(time_frame.get_steps() / 4 + 1);
  std::vector<std::complex<double>> suscept_nonlin;
  suscept_nonlin.resize(time_frame.get_steps() / 4 + 1);

  for (size_t i = 0; i < trials; i++) {

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
      suscept_lin[j] += suscept_temp_lin[j];
      suscept_nonlin[j] += suscept_temp_nonlin[j];
    }
  }

  int length = time_frame.get_steps() / 4;

  // vectors for everything
  std::vector<double> suscept_lin_real;
  std::vector<double> suscept_lin_imag;
  std::vector<double> suscept_nonlin_real;
  std::vector<double> suscept_nonlin_imag;
  suscept_lin_real.resize(length);
  suscept_lin_imag.resize(length);
  suscept_nonlin_real.resize(length);
  suscept_nonlin_imag.resize(length);

  for (size_t j = 0; j < time_frame.get_steps() / 4; j++) {
    suscept_lin_real[j] += suscept_lin[j].real();
    suscept_lin_imag[j] += suscept_lin[j].imag();
    suscept_nonlin_real[j] += suscept_nonlin[j].real();
    suscept_nonlin_imag[j] += suscept_nonlin[j].imag();
  }

  // send data to master
  MPI_Send(suscept_lin_real.data(), length, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  MPI_Send(suscept_lin_imag.data(), length, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
  MPI_Send(suscept_nonlin_real.data(), length, MPI_DOUBLE, 0, 0,
           MPI_COMM_WORLD);
  MPI_Send(suscept_nonlin_imag.data(), length, MPI_DOUBLE, 0, 0,
           MPI_COMM_WORLD);
}
