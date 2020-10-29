/**
 * @file FiringRateSimulation.h
 * @author C.H. Egerland
 */
#ifndef SPIKE_FIRINGRATESIMULATION_H
#define SPIKE_FIRINGRATESIMULATION_H

#include "Spike/Neuron/IF.h"
#include "Spike/SpikeTrain/SpikeTrain.h"
#include "Spike/TimeFrame/TimeFrame.h"

namespace Spike {

/**
 * @brief Implements a simulation during which we calculate the firing rate
 */
class FiringRateSimulation {
private:
  TimeFrame time_frame;           ///< the time frame
  SpikeTrain spike_train;         ///< the spike train
  std::unique_ptr<IF> neuron;     ///< pointer to an IF neuron
  std::unique_ptr<Signal> signal; ///< pointer to a signal

  size_t N_neurons; ///< number of trials

  std::vector<double> firing_rate; ///< array containing the firing rate values

public:
  /**
   * @brief Constructs a firing rate simulation from .ini file
   * @param input_file Path to .ini file
   */
  explicit FiringRateSimulation(const std::string &input_file);

  /**
   * @brief Calculates the firing rate for a given number of trials.
   * @param trials
   */
  virtual void calculate(int trials);

  /**
   * @brief Adds a given vector of firing rate values to the firing_rate array
   * @param tmp_firing_rate Vector containing values of the firing rate
   */
  void add_to_firing_rate(const std::vector<double> &tmp_firing_rate);

  // getter function
  [[nodiscard]] size_t get_N_neurons() const { return N_neurons; };
  [[nodiscard]] size_t get_firing_rate_size() const {
    return firing_rate.size();
  };
  [[nodiscard]] const TimeFrame &get_time_frame() const { return time_frame; };
  [[nodiscard]] const std::vector<double> &get_firing_rate() const {
    return firing_rate;
  };
};

} // namespace Spike

#endif // SPIKE_FIRINGRATESIMULATION_H
