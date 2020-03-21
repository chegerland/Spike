#ifndef PIF_H
#define PIF_H

#include "IF.h"

/**
 * @class PIF
 * @brief Implement a perfect integrate-and-fire (PIF) neuron.
 */
class PIF : public IF {
public:
  /**
   * @brief Construct PIF from parameters
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  PIF(double mu, double D);

  /**
   * @brief Construct PIF from input file
   * @param input_file Input file in .json format.
   */
  PIF(const std::string& input_file);

  /**
   * @brief Returns drift of the PIF neuron, i.e. mu
   * @param v Voltage
   * @param t time
   * @return Drift of PIF, i.e. mu
   */
  double drift(double v, double t) const;
};

#endif // PIF_H
