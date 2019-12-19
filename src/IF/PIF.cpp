#include "PIF.h"

// drift of a PIF neuron
double PIF::drift(double v, double t) const
{
  return this->mu;
};
