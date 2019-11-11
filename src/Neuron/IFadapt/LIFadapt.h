#ifndef LIFADAPT_H
#define LIFADAPT_H

#include "IFadapt.h"

/*!
* Implements a leaky integrate and fire (IF) model with adaptation.
* This is a subclass of the generic IFadapt model, see that page for more documentation.
*/
class LIFadapt : public IFadapt
{
public:

  /*!
  * Constructor of a leaky integrate and fire neuron with adaptation.
  * @param mu mu
  * @param D D
  * @param Delta Delta
  * @param tau_a tau_a
  */
  LIFadapt(double mu, double D, double Delta, double tau_a);

  /*!
  * Constructor of a leaky integrate and fire neuron with adaptation from .json file
  * @param input_file .json file with parameters
  */
  LIFadapt(std::string input_file);

  /*!
  * Returns drift of a leaky IF neuron with adaptation
  * @param v Voltage
  * @param t Time
  */
  double drift(double v, double t) const;

  /*!
  * Print parameters of the LIFadapt neuron.
  */
  void print_parameters() const;

  /*!
  * Function for finding roots for limit cycle
  */
  double func(double x) const;

  /*!
  * Function returning the limit cycle period using bisection.
  * @param x_lo lower bound
  * @param x_hi upper bound
  * @param epserr desired accuracy
  * @param maxiter maximum number of iterations
  */
  double limit_cycle_period(double x_lo, double x_hi, double epserr, int max_iter) const;

  /*!
  * Prints the limit cycle for the deterministic case into vectors.
  * @param curve_v Vector to place the values of the voltages
  * @param curve_a Vector to place the values of the adaptation current
  */
  void limit_cycle(std::vector<double> &curve_v, std::vector<double> &curve_a) const;
};


#endif // LIFADAPT_H
