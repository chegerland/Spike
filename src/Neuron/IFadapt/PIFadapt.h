#ifndef PIFADAPT_H
#define PIFADAPT_H

#include "IFadapt.h"

/*!
* Implements a perfect integrate and fire (IF) model with adaptation.
* This is a subclass of the generic IFadapt model, see that page for more documentation.
*/
class PIFadapt : public IFadapt
{
public:

  /*!
  * Constructor of a perfect integrate and fire neuron with adaptation.
  * @param mu mu
  * @param D D
  * @param Delta Delta
  * @param tau_a tau_a
  */
  PIFadapt(double mu, double D, double Delta, double tau_a);

  /*!
  * Constructor of a perfect integrate and fire neurons with adaptation from .json file
  * @param input_file .json file with parameters
  */
  PIFadapt(std::string input_file);

  /*!
  * Returns drift of a perfect IF neuron with adaptation
  * @param v Voltage
  * @param t Time
  */
  double drift(double v, double t) const;

  /*!
  * Print parameters of the PIFadapt neuron
  */
  void print_parameters() const;

  /*!
  * Prints the limit cycle for the deterministic case into vectors.
  * @param curve_v Vector to place the values of the voltages
  * @param curve_a Vector to place the values of the adaptation current
  */
  void limit_cycle(std::vector<double> &curve_v, std::vector<double> &curve_a) const;

};

#endif // PIFadapt_H
