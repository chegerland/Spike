#include <iostream>
#include <vector>
#include <getopt.h>

#include "IO/input_output.h"
#include "Neuron/neuron.h"


// main
int main(int argc, char *argv[])
{
  struct Files files; 
 
  options(&files, argc, argv);

  std::cout << files.input_file << std::endl;
  std::cout << files.output_file << std::endl;

  PIF pif_neuron;

  double t_0 = 0;
  double t_end = 8;
  double dt = 1e-3;

  double mu = 1;
  double D = 0.02;

  pif_neuron.set_simulation_params(t_0, t_end, dt);
  pif_neuron.set_if_params(mu, D);

  pif_neuron.simulation(&files, 10);

}
