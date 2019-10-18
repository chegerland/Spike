#include <iostream>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "ProgressBar.hpp"

#include "Simulation.h"
#include "../Neuron/NeuronFactory.h"
#include "../Signal/SignalFactory.h"


// constructor from file
Simulation::Simulation(std::string input_file)
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // Read time frame parameters
  time->t_0 = root.get<double>("Simulation.t_0");
  time->t_end = root.get<double>("Simulation.t_end");
  time->dt = root.get<double>("Simulation.dt");

  // Read simulation count
  N = root.get<int>("Simulation.N");

  // Read in Neuron
  this->neuron = NeuronFactory::create(input_file);

  // Read in signal
  if ( signal_given(input_file) )
  {
    this->signal = SignalFactory::create(input_file);
  }
  else
  {
    this->signal = NULL;
  };

  // set input file
  this->parameters = input_file;
};

void Simulation::simulate() const
{
  std::ofstream file;
  std::string name = this->parameters.substr(0,this->parameters.find_last_of('.'))+".out";
  file.open(name);

  // progress bar
  ProgressBar progbar(this->N, 70);

  //#pragma omp parallel for
  // run the simulation
  for (int i = 0; i < this->N; i++)
  {
    std::vector<double> spikes; // vector to store spike times in
    spikes = neuron->spike_train(time); // get spike times

    //#pragma omp critical
    // print spike times to files
    for (int i = 0; i < spikes.size(); i++)
    {
      file << spikes[i] << " ";
    };

    // clear spike times vector and start a new line in the file
    spikes.clear();
    file << "\n";

    // Progress
    //#pragma omp critical
    {
      ++progbar;
      progbar.display();
    }
  };

  // close file
  file.close();

  // close progress bar
  progbar.done();

};

// print parameters to standard output
void Simulation::print_parameters()
{
  std::cout << "Simulation parameters: \n"
  << "t_0 = "    << time->t_0 << "\n"
  << "t_end = "  << time->t_end << "\n"
  << "dt = "     << time->dt << "\n"
  << "N = "      << N << "\n"
  << std::endl;
};
