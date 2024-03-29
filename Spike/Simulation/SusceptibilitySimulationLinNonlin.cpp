#include "Spike/Simulation/SusceptibilitySimulationLinNonlin.h"

#include "Spike/Statistics/statistics.h"

namespace Spike {

SusceptibilitySimulationLinNonlin::SusceptibilitySimulationLinNonlin(
    const std::string &input_file)
    : SusceptibilitySimulation(input_file),
      suscept_lin(time_frame.get_size() / 2 + 1, 0),
      suscept_nonlin_diag(time_frame.get_size() / 4 + 1, 0),
      suscept_nonlin_antidiag(time_frame.get_size() / 4 + 1, 0) {}

void SusceptibilitySimulationLinNonlin::calculate(size_t trials) {
    for (size_t i = 0; i < trials; i++) {
        // reset spike train and calculate new signal
        spike_train.clear();
        signal.calculate_signal();

        // get spike train
        neuron->get_spikes(signal, spike_train);

        // calculate susceptibility for this spike train
        susceptibility_lin_nonlin(signal, spike_train.get_values(), time_frame,
                                  suscept_lin, suscept_nonlin_diag, suscept_nonlin_antidiag, N_neurons);
    }
}

void SusceptibilitySimulationLinNonlin::add_to_suscepts(
    const std::vector<std::complex<double>> &tmp_lin,
    const std::vector<std::complex<double>> &tmp_nonlin_diag, const std::vector<std::complex<double>> &tmp_nonlin_antidiag) {
    assert(tmp_lin.size() == suscept_lin.size());
    assert(tmp_nonlin_diag.size() == suscept_nonlin_diag.size());
    assert(tmp_nonlin_antidiag.size() == suscept_nonlin_antidiag.size());

    for (size_t i = 0; i < tmp_nonlin_diag.size(); i++) {
        suscept_lin[i] += tmp_lin[i];
        suscept_nonlin_diag[i] += tmp_nonlin_diag[i];
        suscept_nonlin_antidiag[i] += tmp_nonlin_antidiag[i];
    }
    for (size_t i = tmp_nonlin_diag.size(); i < tmp_lin.size(); i++) {
        suscept_lin[i] += tmp_lin[i];
    }
}

}  // namespace Spike