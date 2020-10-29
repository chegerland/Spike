/**
 * @file SusceptibilitySimulation.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_SUSCEPTIBILITYSIMULATION_H
#define SPIKE_SUSCEPTIBILITYSIMULATION_H

#include "Spike/Neuron/IF.h"
#include "Spike/Signal/WhiteNoiseSignal.h"
#include "Spike/SpikeTrain/SpikeTrain.h"
#include "Spike/TimeFrame/TimeFrame.h"

namespace Spike {

/**
 * @brief Implements a simulation during which we measure the susceptibility of
 * an integrate-and-fire neuron (with or without adaptation).
 */
class SusceptibilitySimulation {
protected:
  TimeFrame time_frame;       ///< time frame
  SpikeTrain spike_train;     ///< spike train
  WhiteNoiseSignal signal;    ///< white noise signal
  std::unique_ptr<IF> neuron; ///< neuron

  size_t N_neurons; ///< number of neurons (trials)
  double c;         ///< noise split coefficient

public:
  /**
   * @brief Constructs susceptibility simulation from .ini file.
   * @param input_file Path to .ini file
   */
  explicit SusceptibilitySimulation(const std::string &input_file);

  /**
   * @brief Calculates the linear and nonlinear susceptibilities for a given
   * number of trials.
   * Each time the white noise signal gets generated again,
   * the neuron produces a new spike train and then the susceptibilities are
   * calculated. The result is then added (!) to the susceptibility vectors.
   * @param trials Number of Trials
   */
  virtual void calculate(int trials) =0;

  // getter function
  [[nodiscard]] size_t get_N_neurons() const { return N_neurons; };
  [[nodiscard]] const TimeFrame &get_time_frame() const { return time_frame; };
  friend std::ostream &operator<<(std::ostream &out,
                                  const SusceptibilitySimulation &suscept_sim);
};

} // namespace Spike

#endif // SPIKE_SUSCEPTIBILITYSIMULATION_H
