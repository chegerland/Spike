#ifndef NEURON_H
#define NEURON_H

#include <math.h>

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

    void set_simulation_params(double a, double b, double c) {
      this->t_0 = a;
      this->t_end = b;
      this->dt = c;
    };

    virtual void spike_times(
        std::vector<double> &spikes
        ) const =0;

    void simulation(int N) const;
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
    void set_if_params(double a, double b) {
      this->mu = a;
      this->D = b;
    };

    virtual double drift(double v, double t) const {
      return (this->mu);
    };

    double diffusion(double v, double t) const {
      return sqrt(2*this->D);
    };

    virtual double rate_analytic() const {
      return 1/(this->mu);
    };

    void voltage_curve() const;
    void spike_times(
        std::vector<double> &spikes
        ) const;
};

//! Leaky integrate and fire model
/*!
 * Implements a leaky integrate and fire (IF) model.
 * This is a subclass of the generic IF model, see that page for more documentation.
 */
class LIF : public IF {
  public:
    
    double drift(double v, double t) const {
      return (this->mu - v);
    };

    double rate_analytic() const {
      return 69;
    };
};

//! Leaky integrate and fire model with input signal
/*!
 * Implements a leaky integrate and fire (IF) model with input signal of the form \f$ s(t) = \varepsilon(\alpha \cos(2 \pi f_1 t) + \beta \cos(2 \pi f_2 t))\f$.
 * This is a subclass of the generic IF model, see that page for more documentation.
 */
class LIFsig : public IF {
  private:
    double eps, alpha, beta, phi, f1, f2;

  public:

    double drift(double v, double t) const {
        return (this->mu - v + this->eps*(this->alpha*cos(2.0*M_PI*this->f1*t) + this->beta*cos(2.0*M_PI*this->f2*t)));
    };
};


#endif // ifndef
