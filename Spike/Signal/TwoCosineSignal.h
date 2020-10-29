#ifndef SPIKE_TWOCOSINESIGNAL_H
#define SPIKE_TWOCOSINESIGNAL_H

#include <string>

#include "Spike/Signal/Signal.h"

namespace Spike {

/**
 * @class TwoCosineSignal
 * @brief Implements a signal consisting of two cosine, i.e.
 * alpha*cos(2*pi*f1*t)
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
   * @param time_frame TimeFrame
   */
  TwoCosineSignal(double alpha, double f1, double beta, double f2, double phi,
                  const TimeFrame &time_frame);

  /**
   * @brief Construct TwoCosineSignal from input file
   * @param input_file Input file in .ini format
   */
  TwoCosineSignal(const std::string &input_file, const TimeFrame &time_frame);

  /**
   * @brief Calculates the cosine signal.
   */
  void calculate_signal();

  /**
   * @brief Returns signal, i.e. alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t +
   * phi)
   * @param t Time
   * @return Signal, i.e. alpha*cos(2*pi*f1*t) + beta*cos(2*pi*f2*t + phi)
   */
  [[nodiscard]] double signal(double t) const;

  void print(std::ostream &out) const override {
    out << "TwoCosineSignal(alpha: " << alpha << ", f1: " << f1
        << ", beta: " << beta << ", f2: " << f2 << ", phi: " << phi << ")";
  }
};

} // namespace Spike

#endif // SPIKE_TWOCOSINESIGNAL_H
