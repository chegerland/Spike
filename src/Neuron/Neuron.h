#ifndef NEURON_H
#define NEURON_H

#include <vector>

#include "../Simulation/Timeframe.h"
#include "../Signal/Signal.h"

//! A generic neuron model.
/*!
* Implements a generic neuron model, i.e. a system which takes a time frame
* [t_0, t_end] with time steps dt and returns a spike train in the form of a vector.
* The spike train vector contains only the spike times, since it is easier to
* derive statistics from it.
*/
class Neuron
{
public:
  /*!
  * Simulates the neuron and puts the spike times into the vector spike_train
  * @param spike_train vector filled with the spike times
  * @param times Timeframe object containing t_0, t_end and dt.
  */
  virtual void spike(std::vector<double> &spike_train, Timeframe *times) const =0;

  /*!
  * Simulates the neuron with a signal and puts the spike times into the vector spike_train
  * @param spike_train vector filled with the spike times
  * @param times Timeframe object containing t_0, t_end and dt.
  */
  virtual void spike(std::vector<double> &spike_train, Timeframe *times, Signal *signal) const =0;

  /*!
  * Prints all the parameters of the neuron.
  */
  virtual void print_parameters() const =0;

};

#endif // ifndef
