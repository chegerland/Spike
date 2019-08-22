#ifndef LIF_H
#define LIF_H

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
  * @param[in] a mu
  * @param[in] b D
  */
  LIF(double a, double b);

  /*!
  * Returns drift of a leaky IF neuron.
  * @param[in] v Voltage
  * @param[in] t Time
  */
  double drift(double v, double t) const {
    return (this->mu - v);
  };
};

#endif //LIF_H
