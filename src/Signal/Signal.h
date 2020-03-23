#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

#include "../src/TimeFrame/TimeFrame.h"

/**
 * @class Signal
 * @brief An abstract base class for signals.
 */
class Signal {
protected:
  TimeFrame time_frame;   ///< time frame for get_value
  double *signal_values;  ///< array containing the get_value values

public:
  explicit Signal(const TimeFrame& time_frame);
  virtual ~Signal();

  double get_value(unsigned int i) const;
};

#endif // SIGNAL_H
