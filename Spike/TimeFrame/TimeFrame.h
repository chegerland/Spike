#ifndef SPIKE_TIMEFRAME_H
#define SPIKE_TIMEFRAME_H

#include <cassert>
#include <string>
#include <vector>

namespace Spike {

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

  /**
   * @brief Returns the start time.
   * @return  start time
   */
  [[nodiscard]] double get_t_0() const { return t_0; };

  /**
   * @brief Returns the end time.
   * @return  end time
   */
  [[nodiscard]] double get_t_end() const { return t_end; };

  /**
   * @brief Returns the time step.
   * @return  time step
   */
  [[nodiscard]] double get_dt() const { return dt; };

  /**
   * @brief Returns the size of the time frame.
   * @return  size of the time frame
   */
  [[nodiscard]] size_t get_size() const { return t.size(); };

  /**
   * @brief Returns the time at index i.
   * @return  time at index i
   */
  [[nodiscard]] double get_time(size_t i) const { return t[i]; };

  /**
   * @brief Returns the times vector.
   * @return  times vector
   */
  [[nodiscard]] const std::vector<double> &get_times() const { return t; };

  /**
   * @brief Overloads the operator << so we can print time frame.
   * @param out out stream
   * @param tf time frame
   * @return out stream
   */
  friend std::ostream &operator<<(std::ostream &out, const TimeFrame &tf);
};

} // namespace Spike

#endif // SPIKE_TIMEFRAME_H
