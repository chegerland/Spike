#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <chrono>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

// spike libraries
#include "models.h"
#include "inputoutput.h"
#include "statistics.h"

// auxiliary files needed for spike app
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
    case 0: // Simulation mode
    {
      // define neuron
      Neuron *neuron;
      neuron = NeuronFactory::create(options->parameters);

      // show input parameters to user
      sim->print_parameters();
      neuron->print_parameters();

      // measure time
      auto start = std::chrono::high_resolution_clock::now();

      // simulate the neuron
      simulation(neuron, sim);

      // Record end time
      auto finish = std::chrono::high_resolution_clock::now();

      // print time
      std::chrono::duration<double> elapsed = finish - start;
      std::cout << "Elapsed time: " << elapsed.count() << " s\n";

      break;
    }
    case 1: // Evaluation mode
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
    case 2: // Curves mode
    {

      // read neutron type
      pt::ptree root;
      pt::read_json(options->parameters, root);
      std::string type = root.get<std::string>("Neuron.type");

      // print limit cycle if it is an adapting neuron
        if (type == "PIFadapt")
      {
        IFadapt *neuron;
        neuron = new PIFadapt(options->parameters);

        // show input parameters to user
        sim->print_parameters();
        neuron->print_parameters();

        // print voltage curve
        neuron->voltage_curve(sim);
        neuron->limit_cycle(sim);
      }
      else if (type == "LIFadapt")
      {
        IFadapt *neuron;
        neuron = new LIFadapt(options->parameters);

        // show input parameters to user
        sim->print_parameters();
        neuron->print_parameters();

        // print voltage curve
        neuron->voltage_curve(sim);
        neuron->limit_cycle(sim);
      }
      else
      {
        // define neuron
        Neuron *neuron;
        neuron = NeuronFactory::create(options->parameters);

        // show input parameters to user
        sim->print_parameters();
        neuron->print_parameters();

        // print voltage curve
        neuron->voltage_curve(sim);
      }


      break;
    }
    default:
      std::cerr << "Unknown mode!" << std::endl;
      exit(0);
  };
};
