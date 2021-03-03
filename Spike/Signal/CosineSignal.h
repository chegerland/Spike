/**
 * @file CosineSignal.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_COSINESIGNAL_H
#define SPIKE_COSINESIGNAL_H

#include <ostream>
#include <string>

#include "Spike/Signal/Signal.h"

namespace Spike {

/**
 * @brief Implements a cosine signal, i.e. alpha*cos(2*pi*f*t)
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
  CosineSignal(double alpha, double f, const TimeFrame &time_frame);

  /**
   * @brief Construct CosineSignal from .ini file
   * @param input_file Path to .ini file
   * @param time_frame TimeFrame
   */
  CosineSignal(const std::string &input_file, const TimeFrame &time_frame);

  /**
   * @brief Calculates the cosine signal, i.e. alpha*cos(2*pi*f*t).
   */
  void calculate_signal();

  /**
   * @brief Returns signal at time t, i.e. alpha*cos(2*pi*f*t)
   * @param t Time
   * @return Signal value at t, i.e. alpha*cos(2*pi*f*t)
   */
  [[nodiscard]] double signal(double t) const;

  /**
   * @brief Returns the frequency.
   * @return frequency
   */
  [[nodiscard]] double get_f() const { return this->f; };

  /**
   * @brief Prints cosine signal to out stream.
   * @param out out stream
   */
  void print(std::ostream &out) const override {
    out << "CosineSignal(alpha: " << alpha << ", f: " << f << ")";
  }
};

} // namespace Spike

#endif // SPIKE_COSINESIGNAL_H
