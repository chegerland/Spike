#ifndef COSINESIGNAL_H
#define COSINESIGNAL_H

#include <string>

#include "Signal.h"

/**
 * @class CosineSignal
 * @brief Implements a cosine get_value, i.e. alpha*cos(2*pi*f*t)
 */
class CosineSignal : public Signal {
private:
  double alpha; ///< amplitude
  double f;     ///< frequency

public:
  /**
   * @brief Construct CosineSignal from parameters
   * @param alpha Amplitude
   * @param f Frequency
   * @param time_frame TimeFrame
   */
  CosineSignal(double alpha, double f, const TimeFrame& time_frame);

  /**
   * @brief Construct CosineSignal from input file
   * @param input_file Input file in .json format
   * @param time_frame TimeFrame
   */
  CosineSignal(const std::string& input_file, const TimeFrame& time_frame);

  /**
   * @brief Calculates the cosine get_value.
   */
  void calculate_signal();

  /**
   * @brief Returns get_value, i.e. alpha*cos(2*pi*f*t)
   * @param t Time
   * @return Signal, i.e. alpha*cos(2*pi*f*t)
   */
  double signal(double t) const;

  /**
   * @brief Getter function for the frequency
   * @return The frequency of the get_value f
   */
  double get_f() const { return this->f; };
};

#endif // COSINESIGNAL_H
