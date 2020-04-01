#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#include <cassert>
#include <string>
#include <vector>

//! A time frame class
class TimeFrame {
private:
  double t_0;         ///< start time
  double t_end;       ///< end time
  double dt;          ///< time step
  unsigned int steps; ///< number of time steps
  double *t;          ///< array containing the times

public:
  // constructors
  explicit TimeFrame(const std::string& input_file);
  TimeFrame(double t_0, double t_end, double dt);

  // destructor
  ~TimeFrame();

  // copy
  TimeFrame(const TimeFrame &frame);

  // calculate times
  void calculate_times();

  // getter functions
  double get_t_0() const { return this->t_0; };
  double get_t_end() const { return this->t_end; };
  double get_dt() const { return this->dt; };
  unsigned int get_steps() const { return this->steps; };
  double get_time(unsigned int i) const { return this->t[i]; };

  void print_info(std::ofstream& file);
};

#endif // TIMEFRAME_H
