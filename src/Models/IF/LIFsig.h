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

    /*! overall signal strength */
    double eps;
    /*! amplitude first signal */
    double alpha;
    /*! amplitude second signal */
    double beta;
    /*! phase shift */
    double phi;
    /*! frequency first signal */
    double f1;
    /*! frequency second signal */
    double f2;

  public:
    /*!
     * Returns drift of a leaky IF neuron with two cosine signals.
     * @param v Voltage
     * @param t Time
     */
    double drift(double v, double t) const;
};

#endif //LIFSIG_H
