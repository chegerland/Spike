#ifndef ADAPTATION_H
#define ADAPTATION_H

#include <string>

//! Abstract class for Adaptation
class Adaptation {
public:
  // returns f(a,t) = da/dt
  virtual double adapt(double a, double t) const = 0;

  // reset rule for a(t)
  virtual double reset_rule(double a) const = 0;
};

#endif // ADAPTATION_H
