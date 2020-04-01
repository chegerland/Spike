// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "../../extern/ProgressBar.hpp"
#include "../FiringRate/FiringRateFactory.h"
#include "../Neuron/NeuronFactory.h"
#include "../Signal/SignalFactory.h"
#include "FiringRateSimulation.h"

FiringRateSimulation::FiringRateSimulation(const Options &opts)
    : Simulation(opts) {

  std::string input_file = opts.get_input_file();

  // Create a root
  pt::ptree root;
  pt::read_json(input_file, root);

  // check the type
  std::string type = root.get<std::string>("Simulation.type");
  assert(type == "FiringRateSimulation");

  // read parameters
  this->firing_rate = FiringRateFactory::create(input_file, time_frame);
  this->neuron = NeuronFactory::create(input_file);
  this->N_neurons = (int)root.get<double>("Simulation.N_neurons");

  this->signal_given = root.get<bool>("Simulation.signal");
  if (signal_given) {
    this->signal = SignalFactory::create(input_file, time_frame);
  }
}

FiringRateSimulation::~FiringRateSimulation() {
  delete firing_rate;
  delete signal;
  delete neuron;
}

void FiringRateSimulation::run() {

  // progressbar
  ProgressBar progbar(N_neurons, 70);
  progbar.display();

  // get spike trains
  if (!signal_given) {
#pragma omp parallel for
    for (int i = 0; i < N_neurons; i++) {
      SpikeTrain spike_train(time_frame.get_steps());
      neuron->get_spike_train(time_frame, spike_train);
      firing_rate->add_spike_train(spike_train);

#pragma omp critical
      ++progbar;
#pragma omp critical
      progbar.display();
    }
  } else {
#pragma omp parallel for
    for (int i = 0; i < N_neurons; i++) {
      SpikeTrain spike_train(time_frame.get_steps());
      neuron->get_spike_train(time_frame, *signal, spike_train);
      firing_rate->add_spike_train(spike_train);

#pragma omp critical
      ++progbar;
#pragma omp critical
      progbar.display();
    }
  }

  // calculate the firing rate
  firing_rate->calculate();

  // declare file for output
  std::ofstream file;
  file.open(opts.get_output_file());

  // write info to file
  file << "# FiringRateSimulation"
       << "\n"
       << "#\n";
  neuron->print_info(file);
  file << "#\n";
  time_frame.print_info(file);
  file << "#\n";
  if (signal_given) {
    signal->print_info(file);
  }
  file << "#\n";

  // write firing rate values to file
  double *values = firing_rate->get_values();
  for (unsigned int i = 0; i < time_frame.get_steps(); i++) {
    file << time_frame.get_time(i) << "," << values[i] << "\n";
  }

  // close the file
  file.close();
}
