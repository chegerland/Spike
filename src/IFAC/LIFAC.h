#ifndef LIFAC_H
#define LIFAC_H

#include <string>

#include "IFAC.h"

/**
 * @class LIFAC
 * @brief Implements a leaky integrate-and-fire (LIFAC) neuron.
 */
class LIFAC : public IFAC {
public:
  /**
   * @brief Construct LIFAC from parameters
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  LIFAC(double mu, double D, double tau_a, double Delta);

  /**
   * @brief Construct LIFAC from input file
   * @param input_file input file in .json format.
   */
  explicit LIFAC(const std::string &input_file);

  /**
   * @brief Returns the drift of the LIFAC neuron, i.e. mu - v
   * @param v Voltage
   * @param t Time
   * @return Drift of LIFAC, i.e. mu - v
   */
  double drift(double v) const override;
};

#endif // LIFAC_H
