#include <iostream>
#include <fstream>
#include <vector>
#include <getopt.h>

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
  sim = new Simulation(0, 8, 1e-3, 5);
  sim->output_file = "../data/testOut.out";

  // define new neuron
  PIF *pif_neuron;
  pif_neuron = new PIF(1.0, 0.02);

  // run the simulation
  simulation(pif_neuron, sim);
};
