#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

/**
 * @class Signal
 * @brief An abstract base class for signals.
 */
class Signal {
public:
  /**
   * @brief Returns the signal at time t
   * @param t Time
   * @return Signal at time t
   */
  virtual double signal(double t) const = 0;
};

#endif // SIGNAL_H
