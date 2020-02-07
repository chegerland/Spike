#ifndef ADAPTATION_H
#define ADAPTATION_H

#include <string>

//! Abstract class for Adaptation
class Adaptation {
public:
  // returns f(a,t) = da/dt
  virtual double adapt(double a, double t) = 0;

  // reset rule for a(t)
  virtual double reset_rule(double a) = 0;
};

#endif // ADAPTATION_H
