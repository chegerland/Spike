#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#include <cassert>
#include <string>

//! A time frame class
class Timeframe {
private:
  double t_0;   // start time
  double t_end; // end time
  double dt;    // time step
  int steps;    // number of time steps

public:
  // constructors
  Timeframe(std::string input_file);
  Timeframe(double t_0, double t_end, double dt);

  // getter functions
  double get_t_0() { return this->t_0; };
  double get_t_end() { return this->t_end; };
  double get_dt() { return this->dt; };
  int get_steps() { return this->steps; };

  // print function
  void print_parameters();
};

#endif // TIMEFRAME_H
