#ifndef NEURON_H
#define NEURON_H

#include <vector>

#include "../Simulation/Simulation.h"

//! A generic neuron model.
/*!
* Implements a generic neuron model, i.e. a system which takes a time frame [t_0, t_end] with time steps dt and returns a spike train.
* We however only record the spike times, since it is easier to derive statistics from it.
*/
class Neuron
{
public:

  Neuron(){};
  ~Neuron(){};

  /*!
  * Simulates the neuron and puts the spike times into the vector spikes
  * @param[in] spikes vector filled with the spike times
  * @param[in] simulation simulation object containing t_0, t_end and so on
  */
  virtual void spike_times(
    std::vector<double> &spikes,
    Simulation *simulation
  ) const =0;
};

#endif // ifndef
