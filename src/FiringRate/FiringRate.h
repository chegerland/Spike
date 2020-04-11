/**
 * @file FiringRate.h
 * @author C. H. Egerland
 */

#ifndef FIRINGRATE_H
#define FIRINGRATE_H

#include "../src/SpikeTrain/SpikeTrain.h"
#include "../src/TimeFrame/TimeFrame.h"

/**
 * @class FiringRate
 * @brief Abstract base class for firing rates.
 * This is an abstract class that calculates the firing rate from given spike
 * trains. One can add a spike train to a firing rate with the method
 * add_spike_train, which will do the following: (i) it will increase the
 * N_neurons counter, which counts how many spike trains have been added overall
 * and (ii) it will increase the number of spikes in the spikes histogram, which
 * counts the spikes at a given time (these are of course determined by the time
 * frame).
 * One can calculate the firing rate by calling firing_rate.calculate(). This of
 * course depends on how one actually calculates the firing rate from given
 * spike trains, which is implemented in the subclasses.
 */
class FiringRate {
protected:
  size_t N_Neurons;     ///< number of neurons added to firing rate
  TimeFrame time_frame; ///< time frame
  std::vector<int>
      spike_histogram;        ///< histogram of spikes added to firing rate
  std::vector<double> values; ///< actual values of the firing rate

public:
  /**
   * @brief Constructs the firing rate from a given time frame.
   * @param time_frame
   */
  explicit FiringRate(const TimeFrame &time_frame);

  /**
   * @brief Virtual destructor
   */
  virtual ~FiringRate(){};

  /**
   * @brief Adds a single spike train to the firing rate.
   * This will increase the total neuron counter N_Neurons by one and it will
   * increase the appropriate entry in the spike histogram.
   * @param spike_train Spike train
   */
  void add_spike_train(const SpikeTrain &spike_train);

  /**
   * @brief Clears the neuron counter, values array and spike histogram.
   */
  void clear();

  /**
   * @brief Calculates the firing rate.
   */
  virtual void calculate() = 0;

  /**
   * @brief Getter function for the values vector.
   * @return Reference to vector containing firing rate values
   */
  std::vector<double> &get_values() { return this->values; };

  /**
   * @brief Getter function for a single firing rate value.
   * @param i Index
   * @return Firing rate value at index i
   */
  double get_value(size_t i) { return this->values[i]; };

  /**
   * @brief Prints the firing rate parameters to a given file.
   * @param file File stream.
   */
  virtual void print_info(std::ofstream &file) = 0;

};

#endif // FIRINGRATE_H
