#include <utility>

#include "Simulation.h"

Simulation::Simulation(const Options &opts)
    : opts(opts), time_frame(opts.get_input_file()) {}
