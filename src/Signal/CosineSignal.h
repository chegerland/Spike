/**
 * @file CosineSignal.h
 * @author C. H. Egerland
 */
#ifndef COSINESIGNAL_H
#define COSINESIGNAL_H

#include <string>
#include <ostream>
#include "Signal.h"

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
  CosineSignal(const std::string &input_file,
               const TimeFrame &time_frame);

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

  [[nodiscard]] double get_f() const { return this->f; };

  void print(std::ostream &out) const override {
    out << "CosineSignal(alpha: " << alpha << ", f: " << f << ")";
  }
};

#endif // COSINESIGNAL_H
