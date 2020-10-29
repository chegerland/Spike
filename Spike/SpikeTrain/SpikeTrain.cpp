#include "Spike/SpikeTrain/SpikeTrain.h"

namespace Spike {

SpikeTrain::SpikeTrain(const TimeFrame &time_frame) : dt(time_frame.get_dt()) {
  // resize spike train vector
  spikes.resize(time_frame.get_size());
  clear();
}

[[maybe_unused]] int SpikeTrain::spike_count() {
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

void SpikeTrain::add_spike(size_t i) { spikes[i] += 1. / dt; }

} // namespace Spike