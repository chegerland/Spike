#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#include <cassert>
#include <string>
#include <vector>

/**
 * @brief A time frame with discrete time steps.
 */
class TimeFrame {
private:
  double t_0;            ///< start time
  double t_end;          ///< end time
  double dt;             ///< time step
  std::vector<double> t; ///< vector containing the discretized times

public:
  /**
   * @brief Constructs a time frame from a .ini file.
   * @param input_file Path to .ini file
   */
  explicit TimeFrame(const std::string &input_file);

  /**
   * @brief Constructs a time frame from the given parameters.
   * @param t_0 Start time
   * @param t_end End time
   * @param dt Time step
   */
  TimeFrame(double t_0, double t_end, double dt);

  /**
   * @brief Calculates the discretized times.
   */
  void calculate_times();

  // getter functions
  [[nodiscard]] double get_t_0() const { return t_0; };
  [[nodiscard]] double get_t_end() const { return t_end; };
  [[nodiscard]] double get_dt() const { return dt; };
  [[nodiscard]] size_t get_size() const { return t.size(); };
  [[nodiscard]] double get_time(size_t i) const { return t[i]; };
  [[nodiscard]] const std::vector<double> &get_times() const { return t; };

  friend std::ostream& operator<< (std::ostream &out, const TimeFrame &tf);
};

#endif // TIMEFRAME_H
