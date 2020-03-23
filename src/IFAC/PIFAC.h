#ifndef PIFAC_H
#define PIFAC_H

#include "IFAC.h"

/**
 * @class PIFAC
 * @brief Implement a perfect integrate-and-fire (PIFAC) neuron.
 */
class PIFAC : public IFAC {
public:
  /**
   * @brief Construct PIFAC from parameters
   * @param mu Mean input current
   * @param D Diffusion coefficient
   */
  PIFAC(double mu, double D, double tau_a, double Delta);

  /**
   * @brief Construct PIFAC from input file
   * @param input_file Input file in .json format.
   */
  explicit PIFAC(const std::string& input_file);

  /**
   * @brief Returns drift of the PIFAC neuron, i.e. mu
   * @param v Voltage
   * @param t time
   * @return Drift of PIFAC, i.e. mu
   */
  double drift(double v) const override;
};

#endif // PIFAC_H
