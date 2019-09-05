#ifndef PIF_H
#define PIF_H

#include "IF.h"

//! Perfect integrate and fire model
/*!
* Implements a perfect integrate and fire (IF) model.
* This is a subclass of the generic IF model, see that page for more documentation.
*/
class PIF : public IF
{
public:

  /*!
  * Constructor of a perfect integrate and fire neurons
  * @param a mu
  * @param b D
  */
  PIF(double a, double b);

  /*!
  * Constructor of a perfect integrate and fire neurons from .json file
  * @param input_file .json file with parameters
  */
  PIF(std::string input_file);

  /*!
  * Returns drift of a perfect IF neuron.
  * @param v Voltage
  * @param t Time
  */
  double drift(double v, double t) const;

  /*!
  * Returns analytically calculated firing rate of a perfect IF neuron.
  */
  double rate_analytic() const;

  /*!
  * Print parameters of the PIF neuron
  */
  void print_parameters();
};

#endif // PIF_H
