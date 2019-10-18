#ifndef NEURON_H
#define NEURON_H

#include <vector>

#include "../Simulation/Simulation.h"
#include "../Signal/Signal.h"


//! A generic neuron model.
/*!
* Implements a generic neuron model, i.e. a system which takes a time frame [t_0, t_end] with time steps dt and returns a spike train.
* We however only record the spike times, since it is easier to derive statistics from it.
*/
class Neuron
{
public:

  /*!
  * Simulates the neuron and puts the spike times into the vector spikes
  * @param spikes vector filled with the spike times
  * @param simulation simulation object containing t_0, t_end and so on
  */
  virtual void spike_times(std::vector<double> &spikes, Simulation *simulation) const =0;

  /*!
  * Simulates a neuron with signal and puts the spike times into the vector spikes.
  * Per default it calls the routine without a signal.
  * @param spikes vector filled with the spike times
  * @param simulation simulation object containing t_0, t_end and so on
  */
  virtual void spike_times(std::vector<double> &spikes, Simulation *simulation, Signal *signal) const;

  /*!
  * Prints all the parameters of the neuron.
  * Every specific neuron type should have an implementation of this.
  */
  virtual void print_parameters() =0;

  /*!
  * Prints the voltage curve, i.e. the function v(t) into an output file specified by the simulation
  * @param simulation simulation class containing information on the time frame etc.
  */
  virtual void voltage_curve(Simulation *simulation) const =0;
};

#endif // ifndef
