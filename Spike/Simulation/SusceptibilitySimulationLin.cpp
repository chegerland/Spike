#include "Spike/Simulation/SusceptibilitySimulationLin.h"
#include "Spike/Statistics/statistics.h"

namespace Spike {

SusceptibilitySimulationLin::SusceptibilitySimulationLin(
    const std::string &input_file)
    : SusceptibilitySimulation(input_file),
      suscept_lin(time_frame.get_size() / 2 + 1, 0) {}

void SusceptibilitySimulationLin::calculate(size_t trials) {
  for (size_t i = 0; i < trials; i++) {

    // reset spike train and calculate new signal
    spike_train.clear();
    signal.calculate_signal();

    // get spike train
    neuron->get_spikes(signal, spike_train);

    // calculate susceptibility for this spike train
    susceptibility(signal, spike_train.get_values(), time_frame,
                              suscept_lin, N_neurons);
  }
}

void SusceptibilitySimulationLin::add_to_suscepts(
    const std::vector<std::complex<double>> &tmp_lin) {

  assert(tmp_lin.size() == suscept_lin.size());

  for (size_t i = 0; i < tmp_lin.size(); i++) {
    suscept_lin[i] += tmp_lin[i];
  }
}

} // namespace Spike