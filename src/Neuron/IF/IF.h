#ifndef IF_H
#define IF_H

#include <math.h>
#include <vector>

#include "../Neuron.h"

//! A generic integrate and fire model.
/*!
* Implements a generic integrate and fire (IF) neuron.
* This is the superclass of the family of IF neurons, therefore the drift term can be changed by its subclasses.
* Through a simulation we obtain the spike times or voltage curve from this class.
* We can also check the analytic result for the firing rate.
*/
class IF : public Neuron
{
protected:

  /*! Mobility */
  double mu;

  /*! Diffusion coefficient */
  double D;

public:

  /*!
  * Returns the drift of a generic IF model.
  * @param v Voltage
  * @param t Time
  */
  virtual double drift(double v, double t) const =0;

  /*!
  * Returns the diffusion of the IF models which is the same for all of them.
  * @param v Voltage
  * @param t Time
  */
  double diffusion(double v, double t) const;

  /*!
  * Returns the times at which the IF neuron has spiked and puts them into a vector.
  * @param spike_train Vector to put the spike times into.
  * @param times The time frame containing start/end time and the time step.
  */
  void spike(std::vector<double> &spike_train, Timeframe *times) const;

  /*!
  * Returns the times at which the IF neuron has spiked and puts them into a vector.
  * @param spike_train Vector to put the spike times into.
  * @param times The time frame containing start/end time and the time step.
  * @param signal Signal.
  */
  void spike(std::vector<double> &spike_train, Timeframe *times, Signal *signal) const;

  /*!
  * Prints the voltage curve, i.e. the function v(t) into an output file specified by the simulation.
  * @param curve Vector to place values of the curve, i.e. the voltages
  * @param times The time frame containing start/end time and the time step.
  */
  void voltage_curve(std::vector<double> &curve, Timeframe *time) const;

  /*!
  * Prints the voltage curve, i.e. the function v(t) into an output file specified by the simulation.
  * @param curve Vector to place values of the curve, i.e. the voltages
  * @param times The time frame containing start/end time and the time step.
  */
  void voltage_curve(std::vector<double> &curve, Timeframe *time, Signal *signal) const;

};

#endif // IF_H
