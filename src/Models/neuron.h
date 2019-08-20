#ifndef NEURON_H
#define NEURON_H

#include <math.h>

#include"../IO/input_output.h"

//! A generic neuron model.
/*!
 * Implements a generic neuron model, i.e. a system which takes a time frame [t_0, t_end] with time steps dt and returns a spike train.
 * We however only record the spike times, since it is easier to derive statistics from it.
 */
class Neuron {
  protected:
    double t_0, t_end, dt; // Simulation parameters

  public:
    Neuron(){}; // constructor

    /*!
     * Sets the parameters for the simulation
     * @param[in] a Starting time
     * @param[in] b Stop time
     * @param[in] c Time step
     */
    void set_simulation_params(double a, double b, double c) {
      this->t_0 = a;
      this->t_end = b;
      this->dt = c;
    };

    /*!
     * Simulates the neuron and puts the spike times into the vector spikes
     * @param[in] spikes vector filled with the spike times
     */
    virtual void spike_times(
        std::vector<double> &spikes
        ) const =0;

    /*!
     * Runs the simulation of a neuron N times.
     * @param[in] files Files struct with the name of the output file
     * @param[in] N number of times the simulation shall be run
     */
    void simulation(Files *files, int N) const;
};

#endif // ifndef
