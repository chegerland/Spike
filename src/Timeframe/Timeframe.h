#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#include <string>

//! A time frame class
class Timeframe
{
public:

  // start and end time
  double t_0, t_end;

  // time step
  double dt;

  // number of time steps
  int steps;

  Timeframe(double t_0, double t_end, double dt);
  Timeframe(std::string input_file);

  void print_parameters();
};

#endif // TIMEFRAME_H
