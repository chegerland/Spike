/**
 * @file SpikeTrain.h
 * @author C. H. Egerland
 */

#ifndef SPIKETRAIN_H
#define SPIKETRAIN_H

#include <cstddef>
#include <vector>

/**
 * @class SpikeTrain
 * @brief Implements the spike train.
 * The spike train is a vector with a given length. Each entry represents a time
 * bin. If the neuron has spiked during that time, the spike train entry is
 * true, otherwise it is false.
 */
class SpikeTrain {
private:
  size_t length;            ///< length of the spike train
  std::vector<bool> spikes; ///< bool vector containing the spikes

public:
  /**
   * @brief Constructs a spike train with a given length.
   * @param length
   */
  explicit SpikeTrain(size_t length);

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
  void set_spike(unsigned int i);

  /**
   * @brief Getter function for the length of the spike train.
   * @return Length of the spike train.
   */
  size_t get_length() const { return length; };

  /**
   * @brief Getter function for a certain spike.
   * @param i Index of the spike.
   * @return Value of the spike (true if spike occured, false if no spike
   * occured)
   */
  bool get_spike(unsigned int i) const { return spikes[i]; };
};

#endif // SPIKETRAIN_H
