#include "PIF.h"

// constructor for a pif neuron
PIF::PIF(double a, double b)
{
  mu = a;
  D = b;
};

// drift of a PIF neuron
double PIF::drift(double v, double t) const
{
  return mu;
};

// analytic function of the firing rate
double PIF::rate_analytic() const
{
  return 1/mu;
};
