#include "ExpAdaptation.h"

double ExpAdaptation::adapt(double a, double t)
{
  return -1.0/tau_a * a;
};

void ExpAdaptation::reset_rule(double a)
{
  a += Delta;
};
