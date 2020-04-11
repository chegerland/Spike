#include "SpikeTrain.h"

SpikeTrain::SpikeTrain(size_t length) : length(length) {
  // resize spike train vector
  spikes.resize(length);
  clear();
}

int SpikeTrain::spike_count() {
  int count = 0;

  // loop over spike vector, if spike occured, increase counter
  for (size_t i = 0; i < length; i++) {
    if (spikes[i]) {
      count++;
    }
  }
  return count;
}

void SpikeTrain::clear() {
  // fill spike vector with false everywhere
  std::fill(spikes.begin(), spikes.end(), false);
}

void SpikeTrain::set_spike(unsigned int i) { spikes[i] = true; }