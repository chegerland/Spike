#include "SpikeTrain.h"

SpikeTrain::SpikeTrain(unsigned int length) : length(length) {
  // allocate memory for spike array
  spikes = new bool[length];
  clear();
}

SpikeTrain::~SpikeTrain() { delete[] spikes; }

int SpikeTrain::spike_count() {
  int count = 0;
  for (int i = 0; i < length; i++) {
    if (spikes[i]) {
      count++;
    }
  }
  return count;
}

void SpikeTrain::clear() {
  for (int i = 0; i < length; i++) {
    spikes[i] = false;
  }
}

void SpikeTrain::set_spike(unsigned int i) {
  spikes[i] = true;
}