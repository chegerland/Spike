#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

//! A generic signal
class Signal {
public:
  // Returns the signal at time t
  virtual double signal(double t) const = 0;
};

#endif // SIGNAL_H
