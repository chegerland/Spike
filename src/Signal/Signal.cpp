#include "Signal.h"

Signal::Signal(const TimeFrame &time_frame)
    : time_frame(time_frame){
  // allocate memory for get_value array
  signal_values.resize(time_frame.get_steps());
}

double Signal::get_value(unsigned int i) const { return signal_values[i]; }
