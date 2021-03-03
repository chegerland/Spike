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
 * @brief Implements a prototype simulation during which we measure the
 * susceptibility of an integrate-and-fire neuron (with or without adaptation).
 */
class SusceptibilitySimulation {
protected:
  TimeFrame time_frame;       ///< time frame
  SpikeTrain spike_train;     ///< spike train
  WhiteNoiseSignal signal;    ///< white noise signal
  std::unique_ptr<IF> neuron; ///< neuron

  size_t N_neurons; ///< number of neurons (trials)
  double c;         ///< noise split coefficient
  double D;         ///< total noise intensity

public:
  /**
   * @brief Constructs susceptibility simulation from .ini file.
   * @param input_file path to .ini file
   */
  explicit SusceptibilitySimulation(const std::string &input_file);

  /**
   * @brief Calculates the susceptibility for a given
   * number of trials.
   * @param trials number of Trials
   */
  virtual void calculate(size_t trials) = 0;

  /**
   * @brief Sets a new noise split coefficient.
   * @param c_new new noise split coefficient
   */
  void set_c(double c_new);

  /**
   * @brief Returns the number of neurons (trials) for this simulation.
   * @return number of neurons
   */
  [[nodiscard]] size_t get_N_neurons() const { return N_neurons; };

  /**
   * @brief Returns the time frame.
   * @return time frame
   */
  [[nodiscard]] const TimeFrame &get_time_frame() const { return time_frame; };

  /**
   * @brief Overloads the << operator so we can print a simulation.
   * @param out stream
   * @param suscept_sim susceptibility simulation
   * @return
   */
  friend std::ostream &operator<<(std::ostream &out,
                                  const SusceptibilitySimulation &suscept_sim);
};

} // namespace Spike

#endif // SPIKE_SUSCEPTIBILITYSIMULATION_H
