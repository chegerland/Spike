#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

//! A generic signal
/*!
* Implements a signal
*/
class Signal
{
public:

  /*!
  * Returns the signal at time t, per default the signal is zero at all times.
  * @param t time at which the signal shall be evaluated
  */
  virtual double signal(double t) =0;

  /*!
  * Prints signal parameters
  */
  virtual void print_parameters() =0;
};


#endif // SIGNAL_H
