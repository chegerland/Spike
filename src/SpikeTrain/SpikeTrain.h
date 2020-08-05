/**
 * @file SpikeTrain.h
 * @author C. H. Egerland
 */
#ifndef SPIKETRAIN_H
#define SPIKETRAIN_H

#include <cstddef>
#include <memory>
#include <vector>

#include "../TimeFrame/TimeFrame.h"

/**
 * @brief A spike train for discretized times.
 * For a given time discretization with time step dt, a spike train is an array
 * that, at each entry, is either zero if the neuron hasn't spiked or 1/dt if
 * the neuron has spiked.
 */
class SpikeTrain {
private:
  double dt;                  ///< time step
  std::vector<double> spikes; ///< vector containing the spikes

public:
  /**
   * @brief Constructs a spike train from a given time frame.
   * @param time_frame Time frame
   */
  explicit SpikeTrain(const TimeFrame &time_frame);

  /**
   * @brief Counts the number of spikes in the spike train.
   * @return Number of spikes
   */
  int spike_count();

  /**
   * @brief Clears the spike train, i.e. sets all values to zero.
   */
  void clear();

  /**
   * @brief Adds a spike at index i
   * @param i Index of spike
   */
  void add_spike(size_t i);

  // getter functions
  [[nodiscard]] double get_dt() const { return dt; };
  [[nodiscard]] size_t get_size() const { return spikes.size(); };
  [[nodiscard]] bool get_spike(size_t i) const { return (spikes[i] != 0); };
  [[nodiscard]] const std::vector<double> &get_values() const {
    return spikes;
  };
};

#endif // SPIKETRAIN_H
