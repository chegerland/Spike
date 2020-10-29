#include "extern/ProgressBar.hpp"
#include "Spike/Spike.h"

// logging
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
namespace logging = boost::log;

// program options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <fstream>
#include <mpi.h>

using namespace Spike;

void main_process(FiringRateSimulation &firing_rate_sim,
                  const std::string &output_file);
void sub_process(FiringRateSimulation &firing_rate_sim);

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
        "Path to input file (.ini format)");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    // if the help option is given, show the flag description
    if (vm.count("help")) {
      std::cout << "SPIKE FIRING RATE SIMULATION" << std::endl;
      std::cout << "-------------------------------" << std::endl;
      std::cout << "Calculates the firing rate of a "
                   "given neuron."
                << std::endl;
      std::cout << "All parameters have to be defined in a .ini input file."
                << std::endl;
      std::cout << std::endl;
      std::cout << desc << std::endl;
      exit(0);
    }

    if (vm.count("file")) {
      /* set according output file */
      params.output_file =
          params.input_file.substr(0, params.input_file.find_last_of('.')) +
          "_firing_rate.csv";
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

  // create susceptilibity simulation
  FiringRateSimulation firing_rate_sim(input_file);

  // depending on the world rank start either the main process or a sub process
  if (world_rank == 0) {
    BOOST_LOG_TRIVIAL(info) << "Reading parameters from input file "
                            << opts.input_file << ".";

    main_process(firing_rate_sim, opts.output_file);

    BOOST_LOG_TRIVIAL(info) << "Simulation finished."; 
  } else {
    sub_process(firing_rate_sim);
  }

  // finalize mpi
  MPI_Finalize();

  return 0;
}

void main_process(FiringRateSimulation &firing_rate_sim,
                  const std::string &output_file) {

  // initialize logger
  init_logger();
  BOOST_LOG_TRIVIAL(info) << "SPIKE FIRING RATE SIMULATION";

  // get number of neurons
  size_t N_neurons = firing_rate_sim.get_N_neurons();

  // get the world size
  int world_size = 0;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // determine number of trials each process should handle
  // exclude master process
  int trials = ((int)N_neurons) / world_size;

  BOOST_LOG_TRIVIAL(info) << "Sending " << trials << " trials to "
                          << world_size - 1 << " processes.";
  // send number of trials to each process
  for (int i = 1; i < world_size; i++) {
    MPI_Send(&trials, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
  }

  BOOST_LOG_TRIVIAL(info) << "Calculating firing rate.";
  firing_rate_sim.calculate(trials);
  BOOST_LOG_TRIVIAL(info) << "Finished calculation.";
  BOOST_LOG_TRIVIAL(info) << "Receiving values from subprocesses.";

  // receive arrays back from subprocesses
  std::vector<double> tmp_firing_rate(firing_rate_sim.get_firing_rate_size());

  MPI_Status status;
  for (int i = 1; i < world_size; i++) {

    // receive arrays
    MPI_Recv(tmp_firing_rate.data(), (int)firing_rate_sim.get_firing_rate_size(),
             MPI_DOUBLE, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,
             &status);

    // add array to overall firing rate
    firing_rate_sim.add_to_firing_rate(tmp_firing_rate);
  }
  BOOST_LOG_TRIVIAL(info) << "All values received.";

  BOOST_LOG_TRIVIAL(info) << "Writing results to file " << output_file << ".";

  // write susceptibility to file
  std::ofstream file;
  file.open(output_file);

  //file << "#" << suscept_sim;
  file << "#\n";
  file << "# Data format:\n"
       << "# Time, Firing Rate\n";
  file << "#\n";

  auto firing_rate = firing_rate_sim.get_firing_rate();
  auto time_frame = firing_rate_sim.get_time_frame();

  for (size_t i = 0; i < firing_rate_sim.get_firing_rate_size(); i++) {
    file << time_frame.get_time(i) << ","
         << firing_rate[i] << "\n";
  }

  file.close();
}

void sub_process(FiringRateSimulation &firing_rate_sim) {

  int trials = 0;
  MPI_Status status;
  MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

  // calculate firing rate
  firing_rate_sim.calculate(trials);

  // send data to main process
  auto firing_rate = firing_rate_sim.get_firing_rate();

  MPI_Send(firing_rate.data(), (int)firing_rate.size(), MPI_DOUBLE,
           0, 1, MPI_COMM_WORLD);
}
