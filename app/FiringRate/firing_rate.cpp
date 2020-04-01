#include "../../extern/ProgressBar.hpp"
#include "Spike.h"
#include <fstream>

int main(int argc, char *argv[]) {

  // get file from command line
  Options opts(argc, argv);

  FiringRateSimulation simulation(opts);

  simulation.run();
}