#ifndef SIGNAL_H
#define SIGNAL_H

#include <memory>
#include <string>

#include "../src/TimeFrame/TimeFrame.h"

/**
 * @class Signal
 * @brief An abstract base class for signals.
 */
class Signal {
protected:
  std::shared_ptr<const TimeFrame> time_frame;
  std::vector<double> signal_values; ///< array containing the get_value values

public:
  explicit Signal(const std::shared_ptr<const TimeFrame> &time_frame);
  virtual ~Signal() = default;

  double get_value(unsigned int i) const;

  virtual void print_info(std::ofstream &file) const = 0;
};

#endif // SIGNAL_H
