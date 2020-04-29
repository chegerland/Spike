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
 * @class SpikeTrain
 * @brief Implements the spike train.
 * The spike train is a vector with a given length. Each entry represents a time
 * bin. If the neuron has spiked during that time, the spike train entry is
 * true, otherwise it is false.
 */
class SpikeTrain {
private:
  std::shared_ptr<const TimeFrame> time_frame;
  std::vector<double> spikes; ///< bool vector containing the spikes

public:
  /**
   * @brief Constructs a spike train with a given length.
   * @param length
   */
  explicit SpikeTrain(const std::shared_ptr<const TimeFrame> &time_frame);

  /**
   * @brief Counts the number of spikes in the spike train.
   * @return Spike count
   */
  int spike_count();

  /**
   * @brief Clears the spike train, i.e. sets all values to false.
   */
  void clear();

  /**
   * @brief Sets a value to true, i.e. the neuron has spiked.
   * @param i Index at which the neuron has spiked
   */
  void add_spike(size_t i);

  /**
   * @brief Getter function for a certain spike.
   * @param i Index of the spike.
   * @return Value of the spike (true if spike occured, false if no spike
   * occured)
   */
  bool get_spike(size_t i) const { return (spikes[i] != 0); };

  const std::shared_ptr<const TimeFrame> &get_time_frame() {
    return time_frame;
  };

  const std::vector<double> &get_values() const { return spikes; };
};

#endif // SPIKETRAIN_H
