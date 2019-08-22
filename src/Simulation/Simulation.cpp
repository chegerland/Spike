#include "Simulation.h"

// if no N is given, set N to 1
Simulation::Simulation(double a, double b, double c)
{
  t_0 = a;
  t_end = b;
  dt = c;
  N = 1;
};

Simulation::Simulation(double a, double b, double c, int d)
{
  t_0 = a;
  t_end = b;
  dt = c;
  N = d;
};
