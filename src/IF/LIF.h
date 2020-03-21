#ifndef LIF_H
#define LIF_H

#include <string>

#include "../Adaptation/ExpAdaptation.h"
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
  LIF(const std::string &input_file);

  /**
   * @brief Returns the drift of the LIF neuron, i.e. mu - v
   * @param v Voltage
   * @param t Time
   * @return Drift of LIF, i.e. mu - v
   */
  double drift(double v, double t) const;

  /**
   * @brief Returns the function for finding the deterministic limit cycle
   * period of an LIF with exponential adaptation.
   * @param adapt Exponential Adaptation
   * @param x Limit cycle period
   * @return
   */
  double func(ExpAdaptation &adapt, double x);

  /**
   * Finds the period by solving a bisection algorithm to find the root of the
   * function func. This root is then the deterministic limit cycle period.
   * @brief Finds the limit cycle period of an LIF with exponential adaptation.
   * @param adapt Exponential adaptation
   * @return Deterministic limit cycle period of the LIF with exponential
   * adaptation.
   */
  double limit_cycle_period(ExpAdaptation &adapt);
};

#endif // LIF_H
