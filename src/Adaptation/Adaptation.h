#ifndef ADAPTATION_H
#define ADAPTATION_H

#include <string>

/**
 * @class Adaptation
 * @brief Implements an abstract base class for adaptation variable.
 */
class Adaptation {
public:
  /**
   * @brief Returns the "right side" of the equation for the adaptation variable,
   * i.e. f(a,t) = da/dt.
   * @param a Adaptation variable.
   * @param t Time
   * @return The time derivative da/dt
   */
  virtual double adapt(double a, double t) const = 0;

  // reset rule for a(t)
  /**
   * @brief Reset rule for the adaptation variable.
   * @param a Adaptation variable
   * @return The reset adaptation variable
   */
  virtual double reset_rule(double a) const = 0;
};

#endif // ADAPTATION_H
