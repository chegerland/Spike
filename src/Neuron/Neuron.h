/**
 * @file Neuron.h
 * @author C. H. Egerland
 */

#ifndef NEURON_H
#define NEURON_H

#include "../Signal/Signal.h"
#include "../SpikeTrain/SpikeTrain.h"
#include "../TimeFrame/TimeFrame.h"

/**
 * @class Neuron
 * @brief Abstract base class for neurons.
 * This is an abstract class that serves as an abstraction of neuron models.
 * We demand that every neuron model shall produce a spike train when given a
 * time frame as well as an external signal.
 */
class Neuron {
public:
  /**
   * @brief Fills the spike train for a given time frame.
   * @param time_frame Time frame
   * @param spike_train Spike train
   */
  virtual void get_spike_train(const TimeFrame &time_frame,
                               SpikeTrain &spike_train) = 0;

  /**
   * @brief Fills the spike train for a given time frame and signal
   * @param time_frame Time frame
   * @param signal External signal
   * @param spike_train Spike train
   */
  virtual void get_spike_train(const TimeFrame &time, const Signal &signal,
                               SpikeTrain &spike_train) = 0;

  /**
   * @brief Virtual destructor.
   * This is needed for proper memory freeing.
   */
  virtual ~Neuron(){};

  /**
   * @brief Prints the neuron parameters to a given file.
   * @param file File stream.
   */
  virtual void print_info(std::ofstream &file) = 0;
};

#endif // NEURON_H
