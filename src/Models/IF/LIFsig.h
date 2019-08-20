#ifndef LIFSIG_H
#define LIFSIG_H

#include "IF.h"

//! Leaky integrate and fire model with input signal
/*!
 * Implements a leaky integrate and fire (IF) model with input signal of the form \f$ s(t) = \varepsilon(\alpha \cos(2 \pi f_1 t) + \beta \cos(2 \pi f_2 t))\f$.
 * This is a subclass of the generic IF model, see that page for more documentation.
 */
class LIFsig : public IF {
  private:
    double eps, alpha, beta, phi, f1, f2; // signal parameters

  public:
    /*!
     * Returns drift of a leaky IF neuron with two cosine signals.
     * @param[in] v Voltage
     * @param[in] t Time
     */
    double drift(double v, double t) const {
        return (this->mu - v + this->eps*(this->alpha*cos(2.0*M_PI*this->f1*t) + this->beta*cos(2.0*M_PI*this->f2*t)));
    };
};

#endif //LIFSIG_H
