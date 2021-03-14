#include <fstream>
#include <iostream>

// logging
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
namespace logging = boost::log;

// program options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "Spike/Spike.h"

using namespace Spike;

void init_logger() {
    logging::core::get()->set_filter(logging::trivial::severity >=
                                     logging::trivial::info);
}

struct Parameters {
    std::string input_file;
    std::string output_file_rate;
    std::string output_file_raster;
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
            std::cout << "SPIKE RASTER PLOT SIMULATION" << std::endl;
            std::cout << "-------------------------------" << std::endl;
            std::cout << "Calculates the firing rate of a "
                         "given neuron and a raster plot."
                      << std::endl;
            std::cout
                << "All parameters have to be defined in a .ini input file."
                << std::endl;
            std::cout << std::endl;
            std::cout << desc << std::endl;
            exit(0);
        }

        if (vm.count("file")) {
            /* set according output file */
            params.output_file_rate =
                params.input_file.substr(0,
                                         params.input_file.find_last_of('.')) +
                "_firing_rate.csv";
            params.output_file_raster =
                params.input_file.substr(0,
                                         params.input_file.find_last_of('.')) +
                "_raster.csv";
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

    // read command line options
    Parameters opts;
    opts = read_cmd(argc, argv);
    std::string input_file = opts.input_file;

    // create raster plot simulation
    RasterPlot raster_plot_sim(input_file);

    // calculate
    raster_plot_sim.calculate();

    // save all

    // write raster plot to file
    std::ofstream file;
    file.open(opts.output_file_raster);

    const auto &spike_trains = raster_plot_sim.get_spike_trains();

    for (size_t i = 0; i < spike_trains.size(); i++) {
        for (size_t j = 0; j < spike_trains[i].size(); j++) {
            file << spike_trains[i][j];
            if (j < spike_trains[i].size() - 1) {
                file << ",";
            } else {
                file << "\n";
            }
        }
    }

    file.close();


    return 0;
}