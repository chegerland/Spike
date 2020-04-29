#include "SpikeTrain.h"

SpikeTrain::SpikeTrain(const std::shared_ptr<const TimeFrame>& time_frame)
    : time_frame(time_frame) {
  // resize spike train vector
  spikes.resize(time_frame->get_steps());
  clear();
}

int SpikeTrain::spike_count() {
  int count = 0;

  // loop over spike vector, if spike occured, increase counter
  for (double spike : spikes) {
    if (spike != 0) {
      count++;
    }
  }
  return count;
}

void SpikeTrain::clear() {
  // fill spike vector with false everywhere
  std::fill(spikes.begin(), spikes.end(), 0);
}

void SpikeTrain::add_spike(size_t i) {
  spikes[i] += 1. / time_frame->get_dt();
}