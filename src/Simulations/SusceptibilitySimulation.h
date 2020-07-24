/**
 * @file SusceptibilitySimulation.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_SUSCEPTIBILITYSIMULATION_H
#define SPIKE_SUSCEPTIBILITYSIMULATION_H

#include "../Neuron/IF.h"
#include "../Signal/WhiteNoiseSignal.h"
#include "../SpikeTrain/SpikeTrain.h"
#include "../TimeFrame/TimeFrame.h"

class SusceptibilitySimulation {
private:
  TimeFrame time_frame;       ///< time frame
  SpikeTrain spike_train;     ///< spike train
  WhiteNoiseSignal signal;    ///< white noise signal
  std::unique_ptr<IF> neuron; ///< neuron

  size_t N_neurons; ///< number of neurons (trials)
  double c;         ///< noise split coefficient

  std::vector<std::complex<double>> suscept_lin; ///< linear susceptibility
  std::vector<std::complex<double>>
      suscept_nonlin; ///< nonlinear susceptibility

public:
  SusceptibilitySimulation(const std::string &input_file);

  void calculate(int trials);

  void add_to_suscepts(const std::vector<std::complex<double>> &tmp_lin,
                       const std::vector<std::complex<double>> &tmp_nonlin);

  size_t get_N_neurons() const { return N_neurons; };
  size_t get_size_lin() const { return suscept_lin.size(); };
  size_t get_size_nonlin() const { return suscept_nonlin.size(); };
  const std::vector<std::complex<double>> &get_suscept_lin() const {
    return suscept_lin;
  };
  const std::vector<std::complex<double>> &get_suscept_nonlin() const {
    return suscept_nonlin;
  };
  const TimeFrame &get_time_frame() const { return time_frame; };

  friend std::ostream &operator<<(std::ostream &out,
                                  const SusceptibilitySimulation &suscept_sim);
};

#endif // SPIKE_SUSCEPTIBILITYSIMULATION_H
