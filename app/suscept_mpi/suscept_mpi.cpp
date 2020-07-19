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
  int world_rank = 0;
  int world_size = 0;
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
  int world_size = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // determine number of trials each process should handle
  // exclude master process
  int trials = N_neurons / world_size;

  BOOST_LOG_TRIVIAL(info) << "Sending " << trials << " trials to "
                          << world_size - 1 << " processes.";
  // send number of trials to each process
  // MPI_Bcast(&trials, 1, MPI_INT, 0, MPI_COMM_WORLD);
  for (int i = 1; i < world_size; i++) {
    MPI_Send(&trials, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
  }

  // construct time frame and neuron
  const TimeFrame time_frame(input_file);
  WhiteNoiseSignal signal(input_file, time_frame);
  SpikeTrain spike_train(time_frame);
  auto neuron = NeuronFactory::create(input_file);

  // array for susceptibilities
  std::vector<std::complex<double>> suscept_lin(time_frame.get_steps() / 4 + 1);
  std::vector<std::complex<double>> suscept_nonlin(time_frame.get_steps() / 4 +
                                                   1);

  BOOST_LOG_TRIVIAL(info) << "Calculating linear and nonlinear susceptibility.";
  for (int i = 0; i < trials; i++) {

    // array for susceptibility of single neuron
    std::vector<std::complex<double>> suscept_temp_lin(time_frame.get_steps() / 2 + 1);

    std::vector<std::complex<double>> suscept_temp_nonlin(time_frame.get_steps() / 4 + 1);

    // reset spike train and calculate new signal
    spike_train.clear();
    signal.calculate_signal();

    // get spike train
    neuron->get_spikes(signal, spike_train);

    // calculate susceptibility for this spike train
    susceptibility(signal, spike_train.get_values(), time_frame,
                   suscept_temp_lin);
    susceptibility_nonlinear_diag(signal, spike_train.get_values(), time_frame,
                                  suscept_temp_nonlin);

    // add susceptibility of the spike train to overall susceptibility
    for (size_t j = 0; j < time_frame.get_steps() / 4; j++) {
      suscept_lin[j] += 1. / ((double)N_neurons) * suscept_temp_lin[j];
      suscept_nonlin[j] += 1. / ((double)N_neurons) * suscept_temp_nonlin[j];
    }
  }

  int length = (int)time_frame.get_steps() / 4;

  BOOST_LOG_TRIVIAL(info) << "Finished calculation.";

  BOOST_LOG_TRIVIAL(info) << "Receiving values from subprocesses.";

  // receive arrays back from subprocesses
  std::vector<std::complex<double>> tmp_suscept_lin(length);
  std::vector<std::complex<double>> tmp_suscept_nonlin(length);

  MPI_Status status;
  for (int i = 1; i < world_size; i++) {

    // receive arrays
    MPI_Recv(tmp_suscept_lin.data(), length, MPI_CXX_DOUBLE_COMPLEX,
             MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(tmp_suscept_nonlin.data(), length, MPI_CXX_DOUBLE_COMPLEX,
             MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);

    // add array to overall firing rate
    for (int j = 0; j < length; j++) {
      suscept_lin[j] += 1. / ((double)N_neurons) * tmp_suscept_lin[j];
      suscept_nonlin[j] += 1. / ((double)N_neurons) * tmp_suscept_nonlin[j];
    }
  }

  BOOST_LOG_TRIVIAL(info) << "All values received.";
  BOOST_LOG_TRIVIAL(info) << "Writing results to file " << output_file << ".";

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

  int trials = 0;
  MPI_Status status;
  MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

  // construct time frame, neuron, signal and spike_train
  const TimeFrame time_frame(input_file);
  WhiteNoiseSignal signal(input_file, time_frame);
  SpikeTrain spike_train(time_frame);
  auto neuron = NeuronFactory::create(input_file);

  // array for susceptibilities
  std::vector<std::complex<double>> suscept_lin(time_frame.get_steps() / 4 + 1);
  std::vector<std::complex<double>> suscept_nonlin(time_frame.get_steps() / 4 + 1);

  for (int i = 0; i < trials; i++) {

    // array for susceptibility of single neuron
    std::vector<std::complex<double>> suscept_temp_lin(time_frame.get_steps() / 2 + 1);
    std::vector<std::complex<double>> suscept_temp_nonlin(time_frame.get_steps() / 4 + 1);

    // reset spike train and calculate new signal
    spike_train.clear();
    signal.calculate_signal();

    // get spike train
    neuron->get_spikes(signal, spike_train);

    // calculate susceptibility for this spike train
    susceptibility(signal, spike_train.get_values(), time_frame,
                   suscept_temp_lin);
    susceptibility_nonlinear_diag(signal, spike_train.get_values(), time_frame,
                                  suscept_temp_nonlin);

    // add susceptibility of the spike train to overall susceptibility
    for (size_t j = 0; j < time_frame.get_steps() / 4; j++) {
      suscept_lin[j] += suscept_temp_lin[j];
      suscept_nonlin[j] += suscept_temp_nonlin[j];
    }
  }

  int length = (int)time_frame.get_steps() / 4;

  // send data to master
  MPI_Send(suscept_lin.data(), length, MPI_CXX_DOUBLE_COMPLEX, 0, 1,
           MPI_COMM_WORLD);
  MPI_Send(suscept_nonlin.data(), length, MPI_CXX_DOUBLE_COMPLEX, 0, 2,
           MPI_COMM_WORLD);
}
