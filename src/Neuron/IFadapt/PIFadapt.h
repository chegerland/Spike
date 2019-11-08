#ifndef PIFADAPT_H
#define PIFADAPT_H

#include "IFadapt.h"

/*!
* Implements a perfect integrate and fire (IF) model with adaption
* This is a subclass of the generic IFadapt model, see that page for more documentation.
*/
class PIFadapt : public IFadapt
{
public:

  /*!
  * Constructor of a perfect integrate and fire neurons with adaption
  * @param a mu
  * @param b D
  */
  PIFadapt(double a, double b, double c, double d);

  /*!
  * Constructor of a perfect integrate and fire neurons with adaption from .json file
  * @param input_file .json file with parameters
  */
  PIFadapt(std::string input_file);

  /*!
  * Returns drift of a perfect IF neuron with adaption
  * @param v Voltage
  * @param t Time
  */
  double drift(double v, double t) const;

  /*!
  * Print parameters of the PIFadapt neuron
  */
  void print_parameters() const;

  void limit_cycle(std::vector<double> &curve_v, std::vector<double> &curve_a) const;

};

#endif // PIFadapt_H
