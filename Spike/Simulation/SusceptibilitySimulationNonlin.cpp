#include "Spike/Simulation/SusceptibilitySimulationNonlin.h"
#include "Spike/Statistics/statistics.h"

namespace Spike {

SusceptibilitySimulationNonlin::SusceptibilitySimulationNonlin(
    const std::string &input_file)
    : SusceptibilitySimulation(input_file),
      suscept_nonlin(time_frame.get_size() / 4) {

  for(auto & i : suscept_nonlin) {
    i.resize(suscept_nonlin.size());
  }
}

void SusceptibilitySimulationNonlin::calculate(int trials) {
  for (int i = 0; i < trials; i++) {

    // reset spike train and calculate new signal
    spike_train.clear();
    signal.calculate_signal();

    // get spike train
    neuron->get_spikes(signal, spike_train);

    // calculate susceptibility for this spike train
    susceptibility_nonlin(signal, spike_train.get_values(), time_frame,
                          suscept_nonlin, N_neurons);
  }
}

void SusceptibilitySimulationNonlin::add_to_suscepts(
    const std::vector<std::vector<std::complex<double>>> &tmp_nonlin) {

  for (size_t i = 0; i < suscept_nonlin.size(); i++) {
    for (size_t j = 0; j < suscept_nonlin.size(); j++) {
      suscept_nonlin[i][j] += tmp_nonlin[i][j];
    }
  }
}

} // namespace Spike