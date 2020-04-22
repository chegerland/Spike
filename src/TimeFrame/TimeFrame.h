/**
 * @file TimeFrame.h
 * @author C. H. Egerland
 */

#ifndef TIMEFRAME_H
#define TIMEFRAME_H

#include <cassert>
#include <string>
#include <vector>

/**
 * @class TimeFrame
 * @brief Implements a time frame.
 * A time frame has a start time, a stop time and a number of steps or an
 * equivalent time step. The time frame class calculates the times from these
 * values at construction.
 */
class TimeFrame {
private:
  double t_0;            ///< start time
  double t_end;          ///< end time
  double dt;             ///< time step
  size_t steps;          ///< number of time steps
  std::vector<double> t; ///< vector containing the times

public:
  /**
   * @brief Constructs the time frame from a .json input file.
   * @param input_file Input file in .json format
   */
  explicit TimeFrame(const std::string &input_file);

  /**
   * @brief Constructs the time frame from given parameters.
   * @param t_0 Start time
   * @param t_end End time
   * @param dt Time step
   */
  TimeFrame(double t_0, double t_end, double dt);

  /**
   * @brief Calculates the times.
   */
  void calculate_times();

  /**
   * @brief Getter function for the start time.
   * @return The start time
   */
  double get_t_0() const { return this->t_0; };

  /**
   * @brief Getter function for the end time.
   * @return The end time.
   */
  double get_t_end() const { return this->t_end; };

  /**
   * @brief Getter function for the time step.
   * @return The time step.
   */
  double get_dt() const { return this->dt; };

  /**
   * @brief Getter function for total number of time steps.
   * @return Number of time steps
   */
  size_t get_steps() const { return this->steps; };

  /**
   * @brief Getter function for a specific time.
   * @param i Index
   * @return The time at index i
   */
  double get_time(unsigned int i) const { return this->t[i]; };

  /**
   * @brief Prints info to file
   * @param file File stream
   */
  void print_info(std::ofstream &file) const;
};

#endif // TIMEFRAME_H
