#include <fstream>
#include <iostream>
#include <vector>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

// progress bar
#include "ProgressBar.hpp"

#include "simulate.h"
#include "inputoutput.h"

// simulate the neuron
void simulation(Neuron *neuron, Simulation *sim)
{
    std::vector<double> spikes; // vector to store spike times in

    // open filestream
    std::ofstream file;
    file.open(sim->spike_times_file);

    // progress bar
    ProgressBar progbar(sim->N, 70);

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

      // Progress
      ++progbar;
      progbar.display();
    };

    // close file
    file.close();

    // close progress bar
    progbar.done();
};

// hard coded test simulation
void test_simulation()
{
  // define Simulation
  Simulation *sim;
  sim = new Simulation(0, 8, 1e-3, 5);
  sim->spike_times_file = "../data/testOut.out";

  // define new neuron
  PIF *pif_neuron;
  pif_neuron = new PIF(1.0, 0.02);

  // run the simulation
  simulation(pif_neuron, sim);
};
