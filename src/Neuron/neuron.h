#ifndef NEURON_H
#define NEURON_H

#include <math.h>

//! A generic neuron model.
/*!
 * Implements a generic neuron model, i.e. a system which takes a time frame [t_0, t_end] with time steps dt and returns a spike train. 
 * We however only record the spike times, since it is easier to derive statistics from it.
 */
class Neuron {
  public:
    Neuron(){}; // constructor

    // Simulation parameters
    double t_0, t_end, dt;

    virtual void spike_times(
        std::vector<double> &spikes
        ) =0;

    void simulation(int N);
};

//! A generic integrate and fire model.
/*!
 * Implements a generic integrate and fire (IF) neuron, which per default is an perfect integrate and fire model.
 * This is the superclass of the family of IF neurons, therefore the drift term can be changed by its subclasses.
 * Through a simulation we obtain the spike times or voltage curve from this class.
 * We can also check the analytic result for the firing rate.
 */
class IF : public Neuron {
  public:

    double mu, D;

    virtual double drift(double v, double t) {
      return (this->mu);
    };

    double diffusion(double v, double t) {
      return sqrt(2*this->D);
    };

    virtual double rate_analytic() {
      return 1/(this->mu);
    };

    void voltage_curve() const;
    void spike_times(
        std::vector<double> &spikes
        );
};

//! Leaky integrate and fire model
/*!
 * Implements a leaky integrate and fire (IF) model.
 * This is a subclass of the generic IF model, see that page for more documentation.
 */
class LIF : public IF {
  public:
    
    double drift(double v, double t) {
      return (this->mu - v);
    };

    double rate_analytic() {
      return 69;
    };
};

//! Leaky integrate and fire model with input signal
/*!
 * Implements a leaky integrate and fire (IF) model with input signal of the form \f$ s(t) = \varepsilon(\alpha \cos(2 \pi f_1 t) + \beta \cos(2 \pi f_2 t))\f$.
 * This is a subclass of the generic IF model, see that page for more documentation.
 */
class LIFsig : public IF {
  public:
    double eps, alpha, beta, phi, f1, f2;

    double drift(double v, double t) {
        return (this->mu - v + this->eps*(this->alpha*cos(2.0*M_PI*this->f1*t) + this->beta*cos(2.0*M_PI*this->f2*t)));
    };
};


#endif // ifndef
