#include "LIF.h"

// lif constructor 
LIF::LIF(double a, double b)
{
  mu = a;
  D = b;
}

// drift of an LIF neuron
double LIF::drift(double v, double t) const
{
  return (mu - v);
};
