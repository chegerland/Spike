#ifndef STEPSIGNAL_H
#define STEPSIGNAL_H

#include <string>

#include "Signal.h"

/**
 * @class StepSignal
 * @brief Implement a step get_value, i.e. alpha*Theta(t - t_0)
 */
class StepSignal : public Signal {
private:
  double alpha; ///< amplitude
  double t_0;   ///< start time

public:
  /**
   * @brief Construct StepSignal from parameters
   * @param alpha Amplitude
   * @param t_0 Start time
   * @param time_frame TimeFrame
   */
  StepSignal(double alpha, double t_0, const TimeFrame &time_frame);

  /**
   * @brief Construct StepSignal from input file
   * @param input_file Input file in .json format
   * @param time_frame TimeFrame
   */
  StepSignal(const std::string &input_file, const TimeFrame &time_frame);

  /**
   * @brief Calculates the step get_value.
   */
  void calculate_signal();

  /**
   * @brief Returns get_value, i.e. alpha*Theta(t - t_0)
   * @param t Time
   * @return Signal, i.e. alpha*Theta(t - t_0)
   */
  double signal(double t) const;

  void print_info(std::ofstream &file) const override;
};

#endif // STEPSIGNAL_H
