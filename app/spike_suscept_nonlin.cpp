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

void main_process(SusceptibilitySimulationNonlin &suscept_sim,
                  const std::string &output_file);
void sub_process(SusceptibilitySimulationNonlin &suscept_sim);

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
          "_suscept_matrix.csv";
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
  SusceptibilitySimulationNonlin suscept_sim(input_file);

  // depending on the world rank start either the main process or a sub process
  if (world_rank == 0) {
    BOOST_LOG_TRIVIAL(info) << "Reading parameters from input file "
                            << opts.input_file << ".";

    main_process(suscept_sim, opts.output_file);

    BOOST_LOG_TRIVIAL(info) << "Simulation finished."; 
  } else {
    sub_process(suscept_sim);
  }

  // finalize mpi
  MPI_Finalize();

  return 0;
}

void main_process(SusceptibilitySimulationNonlin &suscept_sim,
                  const std::string &output_file) {

  // initialize logger
  init_logger();
  BOOST_LOG_TRIVIAL(info) << "SPIKE SUSCEPTIBILITY SIMULATION";

  // get number of neurons
  size_t N_neurons = suscept_sim.get_N_neurons();

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

  BOOST_LOG_TRIVIAL(info) << "Calculating linear and nonlinear susceptibility.";
  suscept_sim.calculate(trials);

  BOOST_LOG_TRIVIAL(info) << "Finished calculation.";

  BOOST_LOG_TRIVIAL(info) << "Receiving values from subprocesses.";

  // receive arrays back from subprocesses
  std::vector<std::vector<std::complex<double>>> tmp_suscept_nonlin(
      suscept_sim.get_size_nonlin());

  for(size_t i = 0; i < tmp_suscept_nonlin.size(); i++) {
    tmp_suscept_nonlin[i].resize(tmp_suscept_nonlin.size() - i);
  }

  MPI_Status status;
  for (int i = 1; i < world_size; i++) {

    for(size_t j = 0; j < tmp_suscept_nonlin.size(); j++) {
      MPI_Recv(tmp_suscept_nonlin[j].data(), (int)(tmp_suscept_nonlin.size() - j),
               MPI_CXX_DOUBLE_COMPLEX, MPI_ANY_SOURCE, (int)(1 + j), MPI_COMM_WORLD,
               &status);
    }

    // add array to overall firing rate
    suscept_sim.add_to_suscepts(tmp_suscept_nonlin);
  }
  BOOST_LOG_TRIVIAL(info) << "All values received.";

  BOOST_LOG_TRIVIAL(info) << "Writing results to file " << output_file << ".";

  // write susceptibility to file
  std::ofstream file;
  file.open(output_file);

  file << "#" << suscept_sim;
  file << "#\n";
  file << "# Data format:\n"
       << "# Frequency, Re(Suscept_1), Im(Suscept_1), Re(Suscept_2), "
          "Im(Suscept_2)\n";
  file << "#\n";

  auto suscept_nonlin = suscept_sim.get_suscept_nonlin();
  auto time_frame = suscept_sim.get_time_frame();

  for (size_t i = 0; i < suscept_nonlin.size(); i++) {
    for (size_t j = 0; j < suscept_nonlin.size(); j++) {
      if (j < suscept_nonlin.size() - i) {
        file << std::real(suscept_nonlin[i][j]) << ",";
      } else {
        file << 0 << ",";
      }
    }
    file << "\n";
  }

  file.close();
}

void sub_process(SusceptibilitySimulationNonlin &suscept_sim) {

  int trials = 0;
  MPI_Status status;
  MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

  // calculate susceptibility
  suscept_sim.calculate(trials);

  // send data to main process
  auto suscept_nonlin = suscept_sim.get_suscept_nonlin();

  for(size_t j = 0; j < suscept_nonlin.size(); j++) {
    MPI_Send(suscept_nonlin[j].data(), (int)(suscept_nonlin.size() - j),
             MPI_CXX_DOUBLE_COMPLEX, 0, (int)(1 + j), MPI_COMM_WORLD);
  }
}
