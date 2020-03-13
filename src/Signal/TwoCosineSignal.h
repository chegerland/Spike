#ifndef TWOCOSINESIGNAL_H
#define TWOCOSINESIGNAL_H

#include "Signal.h"
#include <string>

/**
 * @class TwoCosineSignal
 * @brief Implements a signal consisting of two cosine, i.e. alpha*cos(2*pi*f1*t)
 * + beta*cos(2*pi*f2*t + phi)
 */
class TwoCosineSignal : public Signal {
private:
  double alpha; ///< amplitude first signal
  double f1;    ///< frequency first signal
  double beta;  ///< amplitude second signal
  double f2;    ///< frequency second signal
  double phi;   ///< phase shift

public:
  /**
   * @brief Construct TwoCosineSignal from parameters
   * @param alpha Amplitude first signal
   * @param f1 Frequency first signal
   * @param beta amplitude second signal
   * @param f2 Frequency second signal
   * @param phi Phase shift
   */
  TwoCosineSignal(double alpha, double f1, double beta, double f2, double phi);

  /**
   * @brief Construct TwoCosineSignal from input file
   * @param input_file Input file in .json format
   */
  TwoCosineSignal(std::string input_file);

  /**
   * @brief Returns signal, i.e. alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)
   * @param t Time
   * @return Signal, i.e. alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)
   */
  double signal(double t) const;
};

#endif // TWOCOSINESIGNAL_H
