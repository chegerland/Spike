#ifndef EXPADAPTATION_H
#define EXPADAPTATION_H

// normal exponentially decaying Adaptation
class ExpAdaptation
{
private:

  // size of kick
  double Delta;

  // time scale
  double tau_a;

public:
  double adapt(double a, double t);
  void reset_rule(double a);

};

#endif // EXPADAPTATION_H
