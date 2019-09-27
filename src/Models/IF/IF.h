#ifndef IF_H
#define IF_H

#include <math.h>
#include <vector>

#include "../Neuron.h"

//! A generic integrate and fire model.
/*!
* Implements a generic integrate and fire (IF) neuron, which per default is an perfect integrate and fire model.
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
  * Is implemented by specific IF model
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
  * @param spikes Vector to put the spike times into
  * @param simulation simulation class containing information on the time frame etc.
  */
  void spike_times(std::vector<double> &spikes, Simulation *simulation) const;

  /*!
  * Prints the voltage curve, i.e. the function v(t) into an output file specified by the simulation
  * @param simulation simulation class containing information on the time frame etc.
  */
  void voltage_curve(Simulation *simulation) const;

};

#endif // IF_H
