#ifndef STEPSIGNAL_H
#define STEPSIGNAL_H

#include <string>

#include "Signal.h"

/**
 * @class StepSignal
 * @brief Implement a step signal, i.e. alpha*Theta(t - t_0)
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
   */
  StepSignal(double alpha, double t_0);

  /**
   * @brief Construct StepSignal from input file
   * @param input_file Input file in .json format
   */
  StepSignal(std::string input_file);

  /**
   * @brief Returns signal, i.e. alpha*Theta(t - t_0)
   * @param t Time
   * @return Signal, i.e. alpha*Theta(t - t_0)
   */
  double signal(double t) const;
};

#endif // STEPSIGNAL_H
