#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>


// spike libraries
#include "models.h"
#include "inputoutput.h"
#include "statistics.h"

// files
#include "Spike/simulate.h"
#include "Spike/ensemble_statistics.h"


// main
int main(int argc, char *argv[])
{
  // read command line options
  Options *options;
  options = new Options();
  get_options(argc, argv, options);

  // check the command line options
  check_options(options);

  // define simulation (reads parameters and sets in and output file)
  Simulation *sim;
  sim = new Simulation(options->parameters);


  // depending on the mode do
  switch (options->mode)
  {
    case 0:
    {
      // define neuron
      Neuron *neuron;
      neuron = NeuronFactory::create(options->parameters);

      // show input parameters to user
      sim->print_parameters();
      neuron->print_parameters();

      // simulate the neuron
      simulation(neuron, sim);
      break;
    }
    case 1:
    {
      // push file containing all spike trains into simulation
      std::cout << "Loading spike trains ..." << std::endl;
      sim->spike_trains = file_to_vector(sim->spike_times_file);

      // calculate statistics
      if (options->rate)
      {
        std::cout << "Calculating rate ..." << std::endl;
        ensemble_firing_rate(sim, options->dt);
      };

      if (options->isi)
      {
        std::cout << "Calculating interspike intervals ..." << std::endl;
        ensemble_isi(sim);
      };
      break;
    }
    default:
      std::cerr << "Unknown mode!" << std::endl;
      exit(0);
  };
};
