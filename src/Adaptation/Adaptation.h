#ifndef ADAPTATION_H
#define ADAPTATION_H

#include <string>

//! Abstract class for Adaptation
class Adaptation {
protected:
  std::string type; // type of adaptation

public:
  // constructors
  Adaptation();
  Adaptation(std::string input_file);

  // returns f(a,t) = da/dt
  virtual double adapt(double a, double t) = 0;

  // reset rule for a(t)
  virtual double reset_rule(double a) = 0;
};

#endif // ADAPTATION_H
