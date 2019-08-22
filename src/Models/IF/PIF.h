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
  * @param[in] a mu
  * @param[in] b D
  */
  PIF(double a, double b);

  /*!
  * Returns drift of a perfect IF neuron.
  * @param[in] v Voltage
  * @param[in] t Time
  */
  double drift(double v, double t) const {
    return (this->mu);
  };

  /*!
  * Returns analytically calculated firing rate of a perfect IF neuron.
  */
  double rate_analytic() const {
    return 1/(this->mu);
  };
};

#endif // PIF_H
