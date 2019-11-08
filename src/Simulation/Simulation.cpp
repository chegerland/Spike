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
  this->time = new Timeframe(input_file);

  // Read simulation count
  N = root.get<int>("Simulation.N");

  // Read in Neuron
  this->neuron = NeuronFactory::create(input_file);

  // Read in signal
  this->signal_given = root.get<bool>("signal");

  if ( this->signal_given )
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

void Simulation::simulate_signal() const
{
  std::ofstream file;
  std::string name = this->parameters.substr(0,this->parameters.find_last_of('.'))+".out";
  file.open(name);

  // progress bar
  ProgressBar progbar(this->N, 70);

  #pragma omp parallel for
  // run the simulation
  for (int i = 0; i < this->N; i++)
  {
    std::vector<double> spikes; // vector to store spike times in
    neuron->spike(spikes, time, signal); // get spike times

    #pragma omp critical
    // print spike times to files
    for (int i = 0; i < spikes.size(); i++)
    {
      file << spikes[i] << " ";
    };

    // clear spike times vector and start a new line in the file
    spikes.clear();
    file << "\n";

    // Progress
    #pragma omp critical
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

void Simulation::simulate() const
{
  std::ofstream file;
  std::string name = this->parameters.substr(0,this->parameters.find_last_of('.'))+".out";
  file.open(name);

  // progress bar
  ProgressBar progbar(this->N, 70);

  #pragma omp parallel for
  // run the simulation
  for (int i = 0; i < this->N; i++)
  {
    std::vector<double> spikes; // vector to store spike times in
    neuron->spike(spikes, time); // get spike times

    #pragma omp critical
    // print spike times to files
    for (int i = 0; i < spikes.size(); i++)
    {
      file << spikes[i] << " ";
    };

    // clear spike times vector and start a new line in the file
    spikes.clear();
    file << "\n";

    // Progress
    #pragma omp critical
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

void Simulation::run() const
{
    if ( signal_given )
    {
      this->simulate_signal();
    }
    else
    {
      this->simulate();
    };
};

// print parameters to standard output
void Simulation::print_parameters()
{
  std::cout << "Simulation parameters:" << std::endl;

  time->print_parameters();
  neuron->print_parameters();

  if (signal_given)
  {
    signal->print_parameters();
  };

  std::cout << "Simulating " << N << " times." << std::endl;
};
