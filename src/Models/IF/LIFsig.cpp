#include "LIFsig.h"

// drift of a lif neuron with signal
double LIFsig::drift(double v, double t) const
{
  return (mu - v + eps*(alpha*cos(2.0*M_PI*f1*t) + beta*cos(2.0*M_PI*f2*t)));
};
