/**
 * @file Neuron.h
 * @author C. H. Egerland
 */

#ifndef NEURON_H
#define NEURON_H

#include "../Signal/Signal.h"
#include "../SpikeTrain/SpikeTrain.h"
#include "../TimeFrame/TimeFrame.h"

class Neuron {
public:
  virtual void get_spikes(SpikeTrain &spike_train) = 0;
  virtual void get_spikes(Signal &signal, SpikeTrain &spike_train) = 0;

  virtual ~Neuron(){};

  virtual void print_info(std::ofstream &file) const = 0;
};

#endif // NEURON_H
