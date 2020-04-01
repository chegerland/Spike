#include <cassert>

#include "FiringRate.h"

FiringRate::FiringRate(const TimeFrame& time_frame): time_frame(time_frame) {
  // set neuron counter to zero
  N_Neurons = 0;

  // allocate memory for arrays
  spike_histogram = new int [time_frame.get_steps()];
  values = new double [time_frame.get_steps()];

  // clear the arrays
  clear();
}

FiringRate::~FiringRate() {
  // free memory
  delete [] spike_histogram;
  delete [] values;
}

void FiringRate::add_spike_train(const SpikeTrain &spike_train) {
  // spike train should have same length as time frame
  assert(spike_train.get_length() == time_frame.get_steps());

  // increase neuron counter
  N_Neurons++;

  // if there is a spike at position i, increase spike histogram at position i
  for (int i = 0; i < spike_train.get_length(); i++) {
    if (spike_train.get_spike(i)) {
      spike_histogram[i] += 1;
    }
  }
}

void FiringRate::clear() {
  // set neuron counter to zero
  N_Neurons = 0;

  // clear the arrays
  for (int i = 0; i < time_frame.get_steps(); i++) {
    spike_histogram[i] = 0;
    values[i] = 0.0;
  }
}

