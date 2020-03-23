#ifndef FIRINGRATE_H
#define FIRINGRATE_H

#include "../src/TimeFrame/TimeFrame.h"
#include "../src/SpikeTrain/SpikeTrain.h"

class FiringRate {
protected:
  unsigned int N_Neurons;
  TimeFrame time_frame;
  int *spike_histogram;
  double *values;

public:
  // constructor
  explicit FiringRate(const TimeFrame& time_frame);

  // destructor
  virtual ~FiringRate();

  // add a single spike_train
  void add_spike_train(const SpikeTrain& spike_train);

  // clear the firing rate array and neuron counter
  void clear();

  // calculate the firing rate
  virtual void calculate() =0;

  // getter function for the values array
  double * get_values() {return this->values;};
};

#endif // FIRINGRATE_H
