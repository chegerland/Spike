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

/**
 * @brief Implements a simulation during which we measure the susceptibility of
 * an integrate-and-fire neuron (with or without adaptation).
 */
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
  /**
   * @brief Constructs susceptibility simulation from .ini file.
   * @param input_file Path to .ini file
   */
  SusceptibilitySimulation(const std::string &input_file);

  /**
   * @brief Calculates the linear and nonlinear susceptibilities for a given
   * number of trials.
   * Each time the white noise signal gets generated again,
   * the neuron produces a new spike train and then the susceptibilities are
   * calculated. The result is then added (!) to the susceptibility vectors.
   * @param trials Number of Trials
   */
  void calculate(int trials);

  /**
   * @brief Adds the given vectors to the susceptibility vectors.
   * @param tmp_lin Vector containing values of linear susceptibility.
   * @param tmp_nonlin  Vector containing values of nonlinear susceptibility.
   */
  void add_to_suscepts(const std::vector<std::complex<double>> &tmp_lin,
                       const std::vector<std::complex<double>> &tmp_nonlin);

  // getter function
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
