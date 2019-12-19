#include "LIF.h"

// drift of an LIF neuron
double LIF::drift(double v, double t) const
{
  return (this->mu - v);
};
