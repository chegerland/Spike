#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#include <string>
#include <cassert>

//! A time frame class
class Timeframe
{
private:
  double t_0;    // start time
  double t_end;  // end time
  double dt;     // time step
  long long int steps;     // number of time steps

public:

  // constructors
  Timeframe(double t_0, double t_end, double dt): t_0(t_0), t_end(t_end), dt(dt) 
    {
        assert(t_end > t_0);
        assert(dt < t_end - t_0);
        this->steps = (int) (t_end - t_0) / dt;
    };
  Timeframe(std::string input_file);

  // getter functions
  double get_t_0(){return this->t_0;};
  double get_t_end(){return this->t_end;};
  double get_dt(){return this->dt;};
  long long int get_steps(){return this->steps;};

  // print function
  void print_parameters();
};

#endif // TIMEFRAME_H
