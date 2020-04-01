#include "Signal.h"

Signal::Signal(const TimeFrame& time_frame): time_frame(time_frame) {
  // allocate memory for get_value array
  signal_values = new double [time_frame.get_steps()];
}

Signal::~Signal() {
  delete [] signal_values;
}

double Signal::get_value(unsigned int i) const {
  return signal_values[i];
}
