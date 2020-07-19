#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#include <cassert>
#include <string>
#include <vector>

class TimeFrame {
private:
  double t_0;            ///< start time
  double t_end;          ///< end time
  double dt;             ///< time step
  size_t steps;          ///< number of time steps
  std::vector<double> t; ///< vector containing the times

public:
  explicit TimeFrame(const std::string &input_file);
  TimeFrame(double t_0, double t_end, double dt);

  void calculate_times();

  [[nodiscard]] double get_t_0() const { return this->t_0; };
  [[nodiscard]] double get_t_end() const { return this->t_end; };
  [[nodiscard]] double get_dt() const { return this->dt; };
  [[nodiscard]] size_t get_steps() const { return this->steps; };
  [[nodiscard]] double get_time(size_t i) const { return this->t[i]; };
  [[nodiscard]] const std::vector<double> &get_times() const {return t;};

  void print_info(std::ofstream &file) const;
};

#endif // TIMEFRAME_H
