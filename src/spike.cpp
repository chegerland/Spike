#include <iostream>
#include <fstream>
#include <vector>
#include <getopt.h>

#include "IO/input_output.h"
#include "Simulation/Simulation.h"
#include "models.h"

void simulation(Neuron *neuron, Simulation *sim)
{
    std::vector<double> spikes; // vector to store spike times in

    // open filestream
    std::ofstream file;
    file.open(sim->output_file);

    // run the simulation
    for (int i = 0; i < sim->N; i++)
    {
      neuron->spike_times(spikes, sim); // get spike times

      // print spike times to files
      for (int i = 0; i < spikes.size(); i++)
      {
        file << spikes[i] << " ";
      };

      // clear spike times vector and start a new line in the file
      spikes.clear();
      file << "\n";
    };

    // close file
    file.close();
};

// main
int main(int argc, char *argv[])
{

  // define Simulation
  Simulation *sim;
  sim = new Simulation();
  sim->t_0 = 0;
  sim->t_end = 8;
  sim->dt = 1e-3;
  sim->N = 10;
  sim->output_file = "../data/testOut.out";

  // define new neuron
  PIF *pif_neuron;
  pif_neuron = new PIF();

  double mu = 1;
  double D = 0.02;

  pif_neuron->set_if_params(mu, D);

  // run the simulation
  simulation(pif_neuron, sim);
};
