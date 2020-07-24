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
 * @brief Abstract base class for Neurons.
 */
class Neuron {
public:
  /**
   * @brief Produces spikes and adds them to the spike train.
   * @param spike_train Spike train
   */
  virtual void get_spikes(SpikeTrain &spike_train) = 0;

  /**
   * @brief Produces spikes while neuron is subject to a signal and adds them to
   * the spike train.
   * @param signal Input signal
   * @param spike_train Spike train
   */
  virtual void get_spikes(Signal &signal, SpikeTrain &spike_train) = 0;

  /**
   * @brief Virtual destructor
   */
  virtual ~Neuron() = default;
};

#endif // NEURON_H
