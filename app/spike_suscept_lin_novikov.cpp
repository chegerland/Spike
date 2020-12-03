#include "Spike/Spike.h"
#include "extern/ProgressBar.hpp"

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

void main_process(std::array<SusceptibilitySimulationLin, 5> &simulation_array,
                  const std::string &output_file);
void sub_process(std::array<SusceptibilitySimulationLin, 5> &simulation_array);

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
      std::cout << "SPIKE LINEAR SUSCEPTIBILITY NOVIKOV SIMULATION"
                << std::endl;
      std::cout << "-------------------------------" << std::endl;
      std::cout << "Calculates the linear susceptibility for a variety of "
                   "noise split coefficients."
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
          "_suscept_novikov.csv";
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
  std::array<SusceptibilitySimulationLin, 5> simulation_array = {
      SusceptibilitySimulationLin(input_file),
      SusceptibilitySimulationLin(input_file),
      SusceptibilitySimulationLin(input_file),
      SusceptibilitySimulationLin(input_file),
      SusceptibilitySimulationLin(input_file)};

  // change the c's
  simulation_array[0].set_c(1e-2);
  simulation_array[1].set_c(1e-1);
  simulation_array[2].set_c(0.5);
  simulation_array[3].set_c(0.9);
  simulation_array[4].set_c(1.0);

  // depending on the world rank start either the main process or a sub process
  if (world_rank == 0) {
    BOOST_LOG_TRIVIAL(info)
        << "Reading parameters from input file " << opts.input_file << ".";

    main_process(simulation_array, opts.output_file);

    BOOST_LOG_TRIVIAL(info) << "Simulation finished.";
  } else {
    sub_process(simulation_array);
  }

  // finalize mpi
  MPI_Finalize();

  return 0;
}

void main_process(std::array<SusceptibilitySimulationLin, 5> &simulation_array,
                  const std::string &output_file) {

  // initialize logger
  init_logger();
  BOOST_LOG_TRIVIAL(info) << "SPIKE SUSCEPTIBILITY SIMULATION";

  // get number of neurons
  auto N_neurons = simulation_array[0].get_N_neurons();

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
  for (auto &simulation : simulation_array) {
    simulation.calculate(trials);
  }

  BOOST_LOG_TRIVIAL(info) << "Finished calculation.";

  BOOST_LOG_TRIVIAL(info) << "Receiving values from subprocesses.";

  // receive arrays back from subprocesses
  std::vector<std::complex<double>> tmp_suscept_lin(
      simulation_array[0].get_size_lin());

  MPI_Status status;
  for (int i = 1; i < world_size; i++) {

    for (size_t j = 0; j < simulation_array.size(); j++) {
      // receive arrays
      MPI_Recv(tmp_suscept_lin.data(), (int)tmp_suscept_lin.size(),
               MPI_CXX_DOUBLE_COMPLEX, MPI_ANY_SOURCE, j, MPI_COMM_WORLD,
               &status);

      // add array to overall susceptibility
      simulation_array[j].add_to_suscepts(tmp_suscept_lin);
    }
  }
  BOOST_LOG_TRIVIAL(info) << "All values received.";

  BOOST_LOG_TRIVIAL(info) << "Writing results to file " << output_file << ".";

  // write susceptibility to file
  std::ofstream file;
  file.open(output_file);

  file << "# Data format:\n"
       << "# Frequency, Values of 1st Suscept, Values of second suscept, ...\n";
  file << "#\n";

  const auto &time_frame = simulation_array[0].get_time_frame();

  for (size_t i = 0; i < simulation_array[0].get_size_lin(); i++) {
    // print frequency
    file << (double)i / (time_frame.get_t_end() - time_frame.get_t_0()) << ",";

    // print susceptibilities
    for (size_t j = 0; j < simulation_array.size(); j++) {
      if (std::imag(simulation_array[j].get_suscept_lin()[i]) < 0) {
        file << std::real(simulation_array[j].get_suscept_lin()[i])
             << std::imag(simulation_array[j].get_suscept_lin()[i]) << "j";
      } else {
        file << std::real(simulation_array[j].get_suscept_lin()[i]) << "+"
             << std::imag(simulation_array[j].get_suscept_lin()[i]) << "j";
      }

      if (j < simulation_array.size() - 1) {
        file << ",";
      } else {
        file << "\n";
      }
    }
  }

  file.close();
}

void sub_process(std::array<SusceptibilitySimulationLin, 5> &simulation_array) {

  int trials;
  MPI_Status status;
  MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

  // calculate susceptibility
  for (size_t i = 0; i < simulation_array.size(); i++) {
    simulation_array[i].calculate(trials);

    const auto &suscept_lin = simulation_array[i].get_suscept_lin();

    MPI_Send(suscept_lin.data(), (int)suscept_lin.size(),
             MPI_CXX_DOUBLE_COMPLEX, 0, i, MPI_COMM_WORLD);
  }
}
