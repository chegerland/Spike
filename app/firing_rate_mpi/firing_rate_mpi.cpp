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
          "_rate.csv";
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

  init_logger();
  BOOST_LOG_TRIVIAL(info) << "SPIKE FIRING RATE SIMULATION";

  // read parameters and construct classes
  BOOST_LOG_TRIVIAL(info) << "Reading parameters from input file " << input_file
                          << ".";
  // read number of neurons
  pt::ptree root;
  pt::read_json(input_file, root);
  int N_neurons = (int)root.get<double>("Simulation.N_neurons");
  bool signal_given = root.get<bool>("Simulation.signal");
  int signal_given_int = (int)signal_given;

  // get the world size
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // determine number of trials each process should handle
  // exclude master process
  int trials = N_neurons / world_size;

  BOOST_LOG_TRIVIAL(info) << "Sending " << trials << " trials to " << world_size - 1
                          << " processes.";
  // send number of trials to each process and if signal is given
  for (int i = 0; i < world_size - 1; i++) {
    MPI_Send(&trials, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
    MPI_Send(&signal_given_int, 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
  }

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

  BOOST_LOG_TRIVIAL(info) << "Calculating " << trials << " trials.";
  // calculate the firing rate
  if (!signal_given) {
    for (size_t i = 0; i < trials; i++) {
      SpikeTrain spike_train(time_frame.get_steps());
      neuron->get_spike_train(time_frame, spike_train);
      firing_rate->add_spike_train(spike_train);
    }
  } else {
    for (size_t i = 0; i < trials; i++) {
      SpikeTrain spike_train(time_frame.get_steps());
      neuron->get_spike_train(time_frame, *signal, spike_train);
      firing_rate->add_spike_train(spike_train);
    }
  }

  // calculate the firing rate
  firing_rate->calculate();

  // vector containing firing rate values
  std::vector<double> firing_rate_values;
  firing_rate_values.resize(time_frame.get_steps());

  // add values from master
  for (size_t j = 0; j < time_frame.get_steps(); j++) {
    firing_rate_values[j] +=
        1. / ((double)N_neurons) * firing_rate->get_value(j);
  }

  BOOST_LOG_TRIVIAL(info) << "Finished calculation.";

  BOOST_LOG_TRIVIAL(info) << "Receiving values from subprocesses.";
  // receive arrays back from subprocesses
  std::vector<double> tmp_array;
  tmp_array.resize(time_frame.get_steps());
  MPI_Status status;
  for (int i = 0; i < world_size - 1; i++) {

    // receive array
    MPI_Recv(tmp_array.data(), time_frame.get_steps(), MPI_DOUBLE,
             MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

    // add array to overall firing rate
    for (size_t j = 0; j < time_frame.get_steps(); j++) {
      firing_rate_values[j] += 1. / ((double)N_neurons) * tmp_array[j];
    }
  }

  BOOST_LOG_TRIVIAL(info) << "All values received.";
  BOOST_LOG_TRIVIAL(info) << "Writing results to file.";

  // declare file for output
  std::ofstream file;
  file.open(output_file);

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
    file << time_frame.get_time(i) << "," << firing_rate_values[i] << "\n";
  }

  // close the file
  file.close();
  BOOST_LOG_TRIVIAL(info) << "Simulation finished.";
}

void minion(const std::string &input_file) {

  // receive number of trials and if signal is given from master
  int trials, signal_given_int;
  MPI_Status status;
  MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  MPI_Recv(&signal_given_int, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

  bool signal_given = (bool)signal_given_int;

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

  // calculate the firing rate
  if (!signal_given) {
    for (size_t i = 0; i < trials; i++) {
      SpikeTrain spike_train(time_frame.get_steps());
      neuron->get_spike_train(time_frame, spike_train);
      firing_rate->add_spike_train(spike_train);
    }
  } else {
    for (size_t i = 0; i < trials; i++) {
      SpikeTrain spike_train(time_frame.get_steps());
      neuron->get_spike_train(time_frame, *signal, spike_train);
      firing_rate->add_spike_train(spike_train);
    }
  }

  // calculate the firing rate
  firing_rate->calculate();

  // vector containing firing_rate_values
  std::vector<double> firing_rate_values = firing_rate->get_values();

  // send data to master
  MPI_Send(firing_rate_values.data(), time_frame.get_steps(), MPI_DOUBLE, 0, 0,
           MPI_COMM_WORLD);
}
