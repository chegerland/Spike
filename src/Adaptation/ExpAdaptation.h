#ifndef EXPADAPTATION_H
#define EXPADAPTATION_H

#include <cassert>
#include <string>

#include "Adaptation.h"

// exponentially decaying Adaptation
class ExpAdaptation : public Adaptation {
private:
  double Delta; // size of kick
  double tau_a; // time scale

public:
  // constructors
  ExpAdaptation(double Delta, double tau_a);
  ExpAdaptation(const std::string& input_file);

  // adaptation f(a,t) = da/dt = - 1/tau_a * a
  double adapt(double a, double t) const;

  // reset rule for a(t): a -> a + Delta
  double reset_rule(double a) const;

  // getter methods
  double get_Delta() const { return this->Delta; };
  double get_tau_a() const { return this->tau_a; };

  // setter methods
  void set_Delta(double Delta) { this->Delta = Delta; };
  void set_tau_a(double tau_a) { this->tau_a = tau_a; };
};

#endif // EXPADAPTATION_H
