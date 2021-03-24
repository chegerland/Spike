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

void main_process(
    std::array<SusceptibilitySimulationLinNonlin, 3> &simulation_array,
    const std::string &output_file);
void sub_process(
    std::array<SusceptibilitySimulationLinNonlin, 3> &simulation_array);

void init_logger() {
    logging::core::get()->set_filter(logging::trivial::severity >=
                                     logging::trivial::info);
}

void help() {
    std::cout << "SPIKE LINEAR SUSCEPTIBILITY NOVIKOV SIMULATION\n"
              << "-------------------------------\n"
              << "Calculates the linear susceptibility for a variety of "
                 "noise split coefficients.\n"
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
    IO io(*help, "_suscept_novikov.csv");
    io.parse_args(argc, argv);
    std::string input_file = io.get_input_file();
    std::string output_file = io.get_output_file();

    // create susceptilibity simulation
    std::array<SusceptibilitySimulationLinNonlin, 3> simulation_array = {
        SusceptibilitySimulationLinNonlin(input_file),
        SusceptibilitySimulationLinNonlin(input_file),
        SusceptibilitySimulationLinNonlin(input_file)};

    // change the c's
    simulation_array[0].set_c(1e-2);
    simulation_array[1].set_c(1e-1);
    simulation_array[2].set_c(1.0);

    // depending on the world rank start either the main process or a sub
    // process
    if (world_rank == 0) {
        BOOST_LOG_TRIVIAL(info)
            << "Reading parameters from input file " << input_file << ".";

        main_process(simulation_array, output_file);

        BOOST_LOG_TRIVIAL(info) << "Simulation finished.";
    } else {
        sub_process(simulation_array);
    }

    // finalize mpi
    MPI_Finalize();

    return 0;
}

void main_process(
    std::array<SusceptibilitySimulationLinNonlin, 3> &simulation_array,
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

    BOOST_LOG_TRIVIAL(info)
        << "Calculating linear and nonlinear susceptibility.";
    for (size_t i = 0; i < simulation_array.size(); i++) {
        simulation_array[i].calculate(trials);
        BOOST_LOG_TRIVIAL(info) << "Finished one simulation.";

        BOOST_LOG_TRIVIAL(info) << "Receiving values from subprocesses.";

        // receive arrays back from subprocesses
        std::vector<std::complex<double>> tmp_suscept_lin(
            simulation_array[0].get_size_lin());
        std::vector<std::complex<double>> tmp_suscept_nonlin(
            simulation_array[0].get_size_nonlin());

        MPI_Status status;
        for (int j = 1; j < world_size; j++) {
            // receive arrays
            MPI_Recv(tmp_suscept_lin.data(), (int)tmp_suscept_lin.size(),
                     MPI_CXX_DOUBLE_COMPLEX, MPI_ANY_SOURCE, 2 * i + 2,
                     MPI_COMM_WORLD, &status);
            MPI_Recv(tmp_suscept_nonlin.data(), (int)tmp_suscept_nonlin.size(),
                     MPI_CXX_DOUBLE_COMPLEX, MPI_ANY_SOURCE, 2 * i + 1,
                     MPI_COMM_WORLD, &status);

            // add array to overall susceptibility
            simulation_array[i].add_to_suscepts(tmp_suscept_lin,
                                                tmp_suscept_nonlin);
            //BOOST_LOG_TRIVIAL(info) << "Received from worker " << j;
        }
        BOOST_LOG_TRIVIAL(info) << "All values received.";
    }

    BOOST_LOG_TRIVIAL(info) << "Finished all calculations.";

    // write susceptibility to file
    std::ofstream file;
    file.open(output_file);

    file << "# Data format:\n"
         << "# Frequency, Values of 1st Suscept, Values of second suscept, "
            "...\n";
    file << "#\n";

    const auto &time_frame = simulation_array[0].get_time_frame();

    for (size_t i = 0; i < simulation_array[0].get_size_nonlin(); i++) {
        // print frequency
        file << (double)i / (time_frame.get_t_end() - time_frame.get_t_0())
             << ",";

        // print susceptibilities
        for (size_t j = 0; j < simulation_array.size(); j++) {
            const auto &value_lin = simulation_array[j].get_suscept_lin()[i];
            const auto &value_nonlin =
                simulation_array[j].get_suscept_nonlin()[i];

            if (std::imag(value_lin) < 0) {
                file << std::real(value_lin) << std::imag(value_lin) << "j";
            } else {
                file << std::real(value_lin) << "+" << std::imag(value_lin)
                     << "j";
            }

            file << ",";

            if (std::imag(value_nonlin) < 0) {
                file << std::real(value_nonlin) << std::imag(value_nonlin)
                     << "j";
            } else {
                file << std::real(value_nonlin) << "+"
                     << std::imag(value_nonlin) << "j";
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

void sub_process(
    std::array<SusceptibilitySimulationLinNonlin, 3> &simulation_array) {
    int trials;
    MPI_Status status;
    MPI_Recv(&trials, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

    // calculate susceptibility
    for (size_t i = 0; i < simulation_array.size(); i++) {
        simulation_array[i].calculate(trials);

        const auto &suscept_lin = simulation_array[i].get_suscept_lin();
        const auto &suscept_nonlin = simulation_array[i].get_suscept_nonlin();

        MPI_Send(suscept_lin.data(), (int)suscept_lin.size(),
                 MPI_CXX_DOUBLE_COMPLEX, 0, 2 * i + 2, MPI_COMM_WORLD);
        MPI_Send(suscept_nonlin.data(), (int)suscept_nonlin.size(),
                 MPI_CXX_DOUBLE_COMPLEX, 0, 2 * i + 1, MPI_COMM_WORLD);
    }
}
