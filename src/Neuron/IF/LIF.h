#ifndef LIF_H
#define LIF_H

#include <string>

#include "IF.h"

//! Leaky integrate and fire model
/*!
* Implements a leaky integrate and fire (IF) model.
* This is a subclass of the generic IF model, see that page for more documentation.
*/
class LIF : public IF
{
public:

  /*!
  * Constructor of a leaky integrate and fire model
  * @param a mu
  * @param b D
  */
  LIF(double a, double b);


  /*!
  * Constructor of a leaky integrate and fire model from .json file
  * @param input_file .json file with parameters
  */
  LIF(std::string input_file);

  /*!
  * Returns drift of a leaky IF neuron.
  * @param v Voltage
  * @param t Time
  */
  double drift(double v, double t) const;

  /*!
  * Returns analytically calculated firing rate of a leaky IF neuron.
  */
  double rate_analytic() const;

  /*!
  * Print parameters of the PIF neuron
  */
  void print_parameters() const;
};

#endif //LIF_H
