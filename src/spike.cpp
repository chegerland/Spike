#include <iostream>
#include <vector>
#include <getopt.h>

#include "IO/input_output.h"
#include "models.h"


// main
int main(int argc, char *argv[])
{
  // get file names from command line options
  struct Files files;
  options(&files, argc, argv);
  std::cout << files.input_file << std::endl;
  std::cout << files.output_file << std::endl;

  // define new neuron
  PIF *pif_neuron;
  pif_neuron = new PIF();

  // set parameters
  double t_0 = 0;
  double t_end = 8;
  double dt = 1e-3;

  double mu = 1;
  double D = 0.02;

  pif_neuron->set_simulation_params(t_0, t_end, dt);
  pif_neuron->set_if_params(mu, D);

  // run the simulation
  pif_neuron->simulation(&files, 10);

}
