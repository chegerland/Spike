#ifndef EXPADAPTATION_H
#define EXPADAPTATION_H

#include <string>

#include "Adaptation.h"

// normal exponentially decaying Adaptation
class ExpAdaptation : public Adaptation
{
private:

  // size of kick
  double Delta;

  // time scale
  double tau_a;

public:

  ExpAdaptation(std::string input_file);

  double adapt(double a, double t);
  void reset_rule(double a);

};

#endif // EXPADAPTATION_H
