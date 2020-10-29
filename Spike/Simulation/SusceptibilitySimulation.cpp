// ini parser
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

#include "Spike/Neuron/NeuronFactory.h"
#include "Spike/Simulation/SusceptibilitySimulation.h"
#include "Spike/Statistics/statistics.h"

namespace Spike {

SusceptibilitySimulation::SusceptibilitySimulation(
    const std::string &input_file)
    : time_frame(input_file), spike_train(time_frame),
      signal(0.0, 0.0, 1.0 / (2. * time_frame.get_dt()), time_frame) {

  // create neuron
  neuron = NeuronFactory::create(input_file);

  // read parameters
  pt::ptree root;
  pt::read_ini(input_file, root);

  N_neurons = root.get<size_t>("Simulation.N_neurons");
  c = root.get<double>("Simulation.c");

  // change noise intensity and diffusion coefficient
  double D = neuron->get_D();
  neuron->set_D(D * (1.0 - c));
  signal.set_alpha(D * c);
}

std::ostream &operator<<(std::ostream &out,
                         const SusceptibilitySimulation &suscept_sim) {
  out << "SusceptibilitySimulation(c: " << suscept_sim.c
      << ", N_neurons: " << suscept_sim.N_neurons << ")";
  out << suscept_sim.time_frame;
  out << suscept_sim.signal;
  out << *suscept_sim.neuron;
  return out;
}

} // namespace Spike