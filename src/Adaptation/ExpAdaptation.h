#ifndef EXPADAPTATION_H
#define EXPADAPTATION_H

#include <cassert>
#include <string>

#include "Adaptation.h"

/**
 * @class ExpAdaptation
 * @brief Implements the exponential adaptation, i.e. where adaptation variable
 * follows the equation tau_a da/dt = -a, with the reset rule a -> a + Delta.
 */
class ExpAdaptation : public Adaptation {
private:
  double Delta; ///< size of kick
  double tau_a; ///< adaptation time scale

public:
  /**
   * @brief Constructs ExpAdaptation from parameters
   * @param Delta Size of the kick
   * @param tau_a Adaptation time scale
   */
  ExpAdaptation(double Delta, double tau_a);

  /**
   * @brief Constructs ExpAdaptation from input_file.
   * @param input_file Input file in .json format.
   */
  ExpAdaptation(const std::string &input_file);

  /**
   * @brief Returns da/dt = -1/tau_a * a
   * @param a Adaptation current
   * @param t time
   * @return Returns da/dt = -1/tau_a * a
   */
  double adapt(double a, double t) const;

  /**
   * @brief Reset rule for adaptation variable
   * @param a Adaptation variable
   * @return Returns a -> a + Delta
   */
  double reset_rule(double a) const;

  /**
   * @brief Getter method for Delta
   * @return Kick size Delta
   */
  double get_Delta() const { return this->Delta; };

  /**
   * @brief Getter method for tau_a
   * @return Adaptation time scale tau_a
   */
  double get_tau_a() const { return this->tau_a; };

  /**
   * @brief Setter method for Delta
   * @param Delta New kick size
   */
  void set_Delta(double Delta) { this->Delta = Delta; };

  /**
   * @brief Setter method for tau_a
   * @param tau_a New adaptation time scale
   */
  void set_tau_a(double tau_a) { this->tau_a = tau_a; };
};

#endif // EXPADAPTATION_H
