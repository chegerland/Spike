#ifndef NEURON_H
#define NEURON_H

#include <vector>

#include "../Simulation/Timeframe.h"
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
  virtual void spike(std::vector<double> &spike_train, Timeframe *times) const =0;

  /*!
  * Simulates a neuron with signal and puts the spike times into the vector spikes.
  * Per default it calls the routine without a signal.
  * @param spikes vector filled with the spike times
  * @param simulation simulation object containing t_0, t_end and so on
  */
  virtual void spike(std::vector<double> &spike_train, Timeframe *times, Signal *signal) const =0;

  /*!
  * Prints all the parameters of the neuron.
  * Every specific neuron type should have an implementation of this.
  */
  virtual void print_parameters() =0;

};

#endif // ifndef
