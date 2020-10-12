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
      signal(0.0, 0.0, 1.0 / (2. * time_frame.get_dt()), time_frame),
      suscept_lin(time_frame.get_size() / 2 + 1, 0),
      suscept_nonlin(time_frame.get_size() / 4 + 1, 0) {

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

void SusceptibilitySimulation::calculate(int trials) {
  for (int i = 0; i < trials; i++) {

    // reset spike train and calculate new signal
    spike_train.clear();
    signal.calculate_signal();

    // get spike train
    neuron->get_spikes(signal, spike_train);

    // calculate susceptibility for this spike train
    susceptibility_lin_nonlin(signal, spike_train.get_values(), time_frame,
                              suscept_lin, suscept_nonlin, N_neurons);
  }
}

void SusceptibilitySimulation::add_to_suscepts(
    const std::vector<std::complex<double>> &tmp_lin,
    const std::vector<std::complex<double>> &tmp_nonlin) {

  assert(tmp_lin.size() == suscept_lin.size());
  assert(tmp_nonlin.size() == suscept_nonlin.size());

  for (size_t i = 0; i < tmp_nonlin.size(); i++) {
    suscept_lin[i] += tmp_lin[i];
    suscept_nonlin[i] += tmp_nonlin[i];
  }

  for (size_t i = tmp_nonlin.size(); i < tmp_lin.size(); i++) {
    suscept_lin[i] += tmp_lin[i];
  }
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