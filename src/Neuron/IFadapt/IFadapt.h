#ifndef IFADAPT_H
#define IFADAPT_H

#include <math.h>
#include <vector>

#include "../Neuron.h"

//! A generic integrate and fire model with adaptation.
/*!
* Implements a generic integrate and fire (IF) neuron, that is subject to spike-triggered
* adaptation.
* This is the superclass similar to those for IF neurons, so every child of this
* class has to implement its own drift term.
* Through a simulation we obtain the spike times or voltage curve from this class.
*/
class IFadapt : public Neuron
{
protected:

  /*! Mobility */
  double mu;

  /*! Diffusion coefficient */
  double D;

  /*! Adaption strength */
  double Delta;

  /*! Adaption time scale */
  double tau_a;

public:

  /*!
  * Returns the drift of a generic IFadapt model.
  * Is implemented by specific IFadapt model
  * @param v Voltage
  * @param t Time
  */
  virtual double drift(double v, double t) const =0;

  /*!
  * Returns the diffusion of the IFadapt models which is the same for all of them.
  * @param v Voltage
  * @param t Time
  */
  double diffusion(double v, double t) const;

  /*!
  * Returns the times at which the IFadapt neuron has spiked and puts them into a vector.
  * @param spike_train Vector to put the spike times into.
  * @param times The time frame containing start/end time and the time step.
  */
  void spike(std::vector<double> &spike_train, Timeframe *times) const;

  /*!
  * Returns the times at which the IFadapt neuron has spiked and puts them into a vector.
  * @param spike_train Vector to put the spike times into.
  * @param times The time frame containing start/end time and the time step.
  * @param signal Signal.
  */
  void spike(std::vector<double> &spike_train, Timeframe *times, Signal *signal) const;

  /*!
  * Prints the voltage curve, i.e. the functions v(t) and a(t) into an output file specified by the simulation.
  * @param curve_v Vector to place the values of the voltages
  * @param curve_a Vector to place the values of the adaptation current
  * @param times The time frame containing start/end time and the time step.
  */
  void voltage_curve(std::vector<double> &curve_v, std::vector<double> &curve_a, Timeframe *times) const;

  /*!
  * Prints the voltage curve, i.e. the functions v(t) and a(t) into an output file specified by the simulation.
  * @param curve_v Vector to place the values of the voltages
  * @param curve_a Vector to place the values of the adaptation current
  * @param times The time frame containing start/end time and the time step.
  * @param signal Signal.
  */
  void voltage_curve(std::vector<double> &curve_v, std::vector<double> &curve_a, Timeframe *times, Signal *signal) const;

  /*!
  * Prints the limit cycle for the deterministic case into vectors.
  * @param curve_v Vector to place the values of the voltages
  * @param curve_a Vector to place the values of the adaptation current
  */
  virtual void limit_cycle(std::vector<double> &curve_v, std::vector<double> &curve_a) const =0;

};

#endif // IFADAPT_H
