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

#include <mpi.h>

#include <fstream>

using namespace Spike;

void main_process(SusceptibilitySimulationLin &suscept_sim,
                  const std::string &output_file);
void sub_process(SusceptibilitySimulationLin &suscept_sim);

void init_logger() {
    logging::core::get()->set_filter(logging::trivial::severity >=
                                     logging::trivial::info);
}

void help() {
    std::cout << "SPIKE LINEAR SUSCEPTIBILITY SIMULATION\n"
              << "--------------------------------------\n"
              << "Calculates the linear susceptibility of a "
                 "given neuron.\n"
              << "All parameters have to be defined in a .ini input file.\n\n";
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
    IO io(*help, "_suscept_lin.csv");
    io.parse_args(argc, argv);
    std::string input_file = io.get_input_file();
    std::string output_file = io.get_output_file();

    // create susceptilibity simulation
    SusceptibilitySimulationLin suscept_sim(input_file);

    // depending on the world rank start either the main process or a sub
    // process
    if (world_rank == 0) {
        BOOST_LOG_TRIVIAL(info)
            << "Reading parameters from input file " << input_file << ".";

        main_process(suscept_sim, output_file);

        BOOST_LOG_TRIVIAL(info) << "Simulation finished.";
    } else {
        sub_process(suscept_sim);
    }

    // finalize mpi
    MPI_Finalize();

    return 0;
}

void main_process(SusceptibilitySimulationLin &suscept_sim,
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

    BOOST_LOG_TRIVIAL(info)
        << "Calculating linear and nonlinear susceptibility.";
    suscept_sim.calculate(trials);

    BOOST_LOG_TRIVIAL(info) << "Finished calculation.";

    BOOST_LOG_TRIVIAL(info) << "Receiving values from subprocesses.";

    // receive arrays back from subprocesses
    std::vector<std::complex<double>> tmp_suscept_lin(
        suscept_sim.get_size_lin());

    MPI_Status status;
    for (int i = 1; i < world_size; i++) {
        // receive arrays
        MPI_Recv(tmp_suscept_lin.data(), (int)suscept_sim.get_size_lin(),
                 MPI_CXX_DOUBLE_COMPLEX, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD,
                 &status);

        // add array to overall firing rate
        suscept_sim.add_to_suscepts(tmp_suscept_lin);
    }
    BOOST_LOG_TRIVIAL(info) << "All values received.";

    BOOST_LOG_TRIVIAL(info) << "Writing results to file " << output_file << ".";

    // write susceptibility to file
    std::ofstream file;
    file.open(output_file);

    file << "#" << suscept_sim;
    file << "#\n";
    file << "# Data format:\n"
         << "# Frequency, Chi_1\n";
    file << "#\n";

    const auto &suscept_lin = suscept_sim.get_suscept_lin();
    const auto &time_frame = suscept_sim.get_time_frame();

    for (size_t i = 0; i < suscept_lin.size(); i++) {
        file << (double)i / (time_frame.get_t_end() - time_frame.get_t_0())
             << ",";

        if (std::imag(suscept_lin[i]) < 0) {
            file << std::real(suscept_lin[i]) << std::imag(suscept_lin[i])
                 << "j";
        } else {
            file << std::real(suscept_lin[i]) << "+"
                 << std::imag(suscept_lin[i]) << "j";
        }
        file << "\n";
    }

    file.close();
}

void sub_process(SusceptibilitySimulationLin &suscept_sim) {
    int trials = 0;
    MPI_Status status;
    MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

    // calculate susceptibility
    suscept_sim.calculate(trials);

    // send data to main process
    const auto &suscept_lin = suscept_sim.get_suscept_lin();

    MPI_Send(suscept_lin.data(), (int)suscept_lin.size(),
             MPI_CXX_DOUBLE_COMPLEX, 0, 1, MPI_COMM_WORLD);
}
