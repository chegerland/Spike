#ifndef COSINESIGNAL_H
#define COSINESIGNAL_H

#include <string>

#include "Signal.h"

/**
 * @class CosineSignal
 * @brief Implements a cosine signal, i.e. alpha*cos(2*pi*f*t)
 */
class CosineSignal : public Signal {
private:
  double alpha; ///< amplitube
  double f;     ///< frequency

public:
  /**
   * @brief Construct CosineSignal from parameters
   * @param alpha Amplitude
   * @param f Frequency
   */
  CosineSignal(double alpha, double f);

  /**
   * @brief Construct CosineSignal from input file
   * @param input_file Input file in .json format
   */
  CosineSignal(std::string input_file);

  /**
   * @brief Returns signal, i.e. alpha*cos(2*pi*f*t)
   * @param t Time
   * @return Signal, i.e. alpha*cos(2*pi*f*t)
   */
  double signal(double t) const;

  /**
   * @brief Getter function for the frequency
   * @return The frequency of the signal f
   */
  double get_f() const { return this->f; };
};

#endif // COSINESIGNAL_H
