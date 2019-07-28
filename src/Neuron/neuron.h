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

//! A generic integrate and fire model.
/*!
 * Implements a generic integrate and fire (IF) neuron, which per default is an perfect integrate and fire model.
 * This is the superclass of the family of IF neurons, therefore the drift term can be changed by its subclasses.
 * Through a simulation we obtain the spike times or voltage curve from this class.
 * We can also check the analytic result for the firing rate.
 */
class IF : public Neuron {
  protected:
    double mu, D;
    
  public:

    /*!
     * Sets the model parameters for a generic IF model
     * @param[in] a mu
     * @param[in] b D
     */
    void set_if_params(double a, double b) {
      this->mu = a;
      this->D = b;
    };

    /*!
     * Returns the drift of a generic IF model.
     * Is implemented by specific IF model
     * @param[in] v Voltage 
     * @param[in] t Time
     */
    virtual double drift(double v, double t) const =0;

    /*!
     * Returns the diffusion of the IF models which is the same for all of them.
     * @param[in] v Voltage 
     * @param[in] t Time
     */
    double diffusion(double v, double t) const {
      return sqrt(2*this->D);
    };

    /*!
     * Returns the voltage curve of a generic IF neuron;
     * NOT IMPLEMENTED YET!
     */
    void voltage_curve() const;

    /*!
     * Returns the times at which the IF neuron has spiked and puts them into a vector.
     * @param[in] spikes Vector to put the spike times into
     */
    void spike_times(
        std::vector<double> &spikes
        ) const;
};

//! Perfect integrate and fire model
/*!
 * Implements a perfect integrate and fire (IF) model.
 * This is a subclass of the generic IF model, see that page for more documentation.
 */
class PIF : public IF {
  public:

    /*!
     * Returns drift of a perfect IF neuron.
     * @param[in] v Voltage
     * @param[in] t Time
     */
    double drift(double v, double t) const {
      return (this->mu);
    };

    /*!
     * Returns analytically calculated firing rate of a perfect IF neuron.
     */
    double rate_analytic() const {
      return 1/(this->mu);
    };
};


//! Leaky integrate and fire model
/*!
 * Implements a leaky integrate and fire (IF) model.
 * This is a subclass of the generic IF model, see that page for more documentation.
 */
class LIF : public IF {
  public:
    /*!
     * Returns drift of a leaky IF neuron.
     * @param[in] v Voltage
     * @param[in] t Time
     */
    double drift(double v, double t) const {
      return (this->mu - v);
    };
};

//! Leaky integrate and fire model with input signal
/*!
 * Implements a leaky integrate and fire (IF) model with input signal of the form \f$ s(t) = \varepsilon(\alpha \cos(2 \pi f_1 t) + \beta \cos(2 \pi f_2 t))\f$.
 * This is a subclass of the generic IF model, see that page for more documentation.
 */
class LIFsig : public IF {
  private:
    double eps, alpha, beta, phi, f1, f2; // signal parameters

  public:
    /*!
     * Returns drift of a leaky IF neuron with two cosine signals.
     * @param[in] v Voltage
     * @param[in] t Time
     */
    double drift(double v, double t) const {
        return (this->mu - v + this->eps*(this->alpha*cos(2.0*M_PI*this->f1*t) + this->beta*cos(2.0*M_PI*this->f2*t)));
    };
};


#endif // ifndef
