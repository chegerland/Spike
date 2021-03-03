#ifndef SPIKE_SPIKETRAIN_H
#define SPIKE_SPIKETRAIN_H

#include <cstddef>
#include <memory>
#include <vector>

#include "Spike/TimeFrame/TimeFrame.h"

namespace Spike {

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
  size_t spike_count();

  /**
   * @brief Clears the spike train, i.e. sets all values to zero.
   */
  void clear();

  /**
   * @brief Adds a spike at index i
   * @param i Index of spike
   */
  void add_spike(size_t i);

  /**
   * @brief Returns time step
   * @return time step
   */
  [[nodiscard]] double get_dt() const { return dt; };

  /**
   * @brief Returns size of spike train (length).
   * @return size of spike train
   */
  [[nodiscard]] size_t get_size() const { return spikes.size(); };

  /**
   * @brief Checks whether there is a spike at index i.
   * @param i index
   * @return true if spike is present, false if not
   */
  [[nodiscard]] bool get_spike(size_t i) const { return (spikes[i] != 0); };

  /**
   * @brief Returns the whole spike train (as a vector)
   * @return spike train vector
   */
  [[nodiscard]] const std::vector<double> &get_values() const {
    return spikes;
  };
};

} // namespace Spike

#endif // SPIKE_SPIKETRAIN_H
