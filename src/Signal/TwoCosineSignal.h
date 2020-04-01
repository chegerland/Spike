#ifndef TWOCOSINESIGNAL_H
#define TWOCOSINESIGNAL_H

#include "Signal.h"
#include <string>

/**
 * @class TwoCosineSignal
 * @brief Implements a get_value consisting of two cosine, i.e.
 * alpha*cos(2*pi*f1*t)
 * + beta*cos(2*pi*f2*t + phi)
 */
class TwoCosineSignal : public Signal {
private:
  double alpha; ///< amplitude first get_value
  double f1;    ///< frequency first get_value
  double beta;  ///< amplitude second get_value
  double f2;    ///< frequency second get_value
  double phi;   ///< phase shift

public:
  /**
   * @brief Construct TwoCosineSignal from parameters
   * @param alpha Amplitude first get_value
   * @param f1 Frequency first get_value
   * @param beta amplitude second get_value
   * @param f2 Frequency second get_value
   * @param phi Phase shift
   * @param time_frame TimeFrame
   */
  TwoCosineSignal(double alpha, double f1, double beta, double f2, double phi,
                  const TimeFrame &time_frame);

  /**
   * @brief Construct TwoCosineSignal from input file
   * @param input_file Input file in .json format
   */
  TwoCosineSignal(const std::string& input_file, const TimeFrame& time_frame);

  /**
   * @brief Calculates the cosine get_value.
   */
  void calculate_signal();

  /**
   * @brief Returns get_value, i.e. alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t +
   * phi)
   * @param t Time
   * @return Signal, i.e. alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)
   */
  double signal(double t) const;


  void print_info(std::ofstream& file) override;
};

#endif // TWOCOSINESIGNAL_H
