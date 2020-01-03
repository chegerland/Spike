#ifndef EXPADAPTATION_H
#define EXPADAPTATION_H

#include <string>
#include <cassert>

#include "Adaptation.h"

// exponentially decaying Adaptation
class ExpAdaptation : public Adaptation
{
private:

  double Delta; // size of kick
  double tau_a; // time scale

public:

  // constructors
  ExpAdaptation(double Delta, double tau_a): Delta(Delta), tau_a(tau_a) {assert(Delta > 0); assert(tau_a > 0);};
  ExpAdaptation(std::string input_file);

  // adaptation f(a,t) = da/dt = - 1/tau_a * a
  double adapt(double a, double t);

  // reset rule for a(t): a -> a + Delta
  void reset_rule(double a);
};

#endif // EXPADAPTATION_H
