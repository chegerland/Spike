#ifndef LIFADAPT_H
#define LIFADAPT_H

#include "IFadapt.h"

/*!
* Implements a leaky integrate and fire (IF) model with adaption
* This is a subclass of the generic IFadapt model, see that page for more documentation.
*/
class LIFadapt : public IFadapt
{
public:

  /*!
  * Constructor of a leaky integrate and fire neurons with adaption
  * @param a mu
  * @param b D
  */
  LIFadapt(double a, double b, double c, double d);

  /*!
  * Constructor of a leaky integrate and fire neurons with adaption from .json file
  * @param input_file .json file with parameters
  */
  LIFadapt(std::string input_file);

  /*!
  * Returns drift of a leaky IF neuron with adaption
  * @param v Voltage
  * @param t Time
  */
  double drift(double v, double t) const;

  void print_parameters() const;

  /*!
  * Function for finding roots for limit cycle
  */
  double func(double x) const;

  /*!
  * Function returning the limit cycle period using a bisection algorithm
  * @param x_lo lower bound
  * @param x_hi upper bound
  * @param epserr desired accuracy
  * @param maxiter maximum number of iterations
  */
  double limit_cycle_period(double x_lo, double x_hi, double epserr, int max_iter) const;

  /*!
  * Prints the limit cycle for the deterministic case into an output file specified by the simulation
  * @param simulation simulation class containing information on the time frame etc.
  */
  void limit_cycle(std::vector<double> &curve_v, std::vector<double> &curve_a) const;
};


#endif // LIFADAPT_H
