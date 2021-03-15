#include <fstream>
#include <iostream>

#include "Spike/Spike.h"

using namespace Spike;

void help() {
    std::cout << "SPIKE RASTER PLOT SIMULATION\n"
              << "----------------------------\n"
              << "Calculates the raster plot for a given neuron.\n"
              << "All parameters have to be defined in a .ini input file.\n";
}

int main(int argc, char *argv[]) {
    // read command line options
    IO io(*help, "_raster.csv");
    io.parse_args(argc, argv);
    std::string input_file = io.get_input_file();
    std::string output_file = io.get_output_file();

    // create raster plot simulation
    RasterPlot raster_plot_sim(input_file);

    // calculate
    raster_plot_sim.calculate();

    // write raster plot to file
    std::ofstream file;
    file.open(output_file);

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