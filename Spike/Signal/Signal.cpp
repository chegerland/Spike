#include "Spike/Signal/Signal.h"

namespace Spike {

Signal::Signal(const TimeFrame &time_frame) : time_frame(time_frame) {
  // allocate memory for get_value array
  signal_values.resize(time_frame.get_size());
}

double Signal::get_value(size_t i) const { return signal_values[i]; }

std::ostream &operator<<(std::ostream &out, const Signal &signal) {
  signal.print(out);
  return out;
}

} // namespace Spike