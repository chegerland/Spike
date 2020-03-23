#ifndef LIF_H
#define LIF_H

#include <string>

#include "IF.h"

/**
 * @class LIF
 * @brief Implements a leaky integrate-and-fire (LIF) neuron.
 */
class LIF : public IF {
public:
  /**
   * @brief Construct LIF from parameters
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  LIF(double mu, double D);

  /**
   * @brief Construct LIF from input file
   * @param input_file input file in .json format.
   */
  explicit LIF(const std::string &input_file);

  /**
   * @brief Returns the drift of the LIF neuron, i.e. mu - v
   * @param v Voltage
   * @param t Time
   * @return Drift of LIF, i.e. mu - v
   */
  double drift(double v) const override;
};

#endif // LIF_H
