#ifndef NEURON_H
#define NEURON_H

#include <math.h>

// defines a general neuron
class neuron {
  public:
    neuron(){}; // constructor

    // Simulation parameters
    double t_0, t_end, dt;

    virtual void spike_times(
        std::vector<double> &spikes
        ) =0;
};

// integrate and fire neuron, defaults to PIF
class IF : public neuron {
  public:

    double mu, D;

    virtual double drift(double v, double t) {
      return (this->mu);
    };

    double diffusion(double v, double t) {
      return sqrt(2*this->D);
    };

    void voltage_curve() const;
    void spike_times(
        std::vector<double> &spikes
        );
};

// Defines leaky integrate and fire neuron
class LIF : public IF {
  public:
    
    double drift(double v, double t) {
      return (this->mu - v);
    };
};

// parameters of an input signal
struct signal_parameters {
    double eps, alpha, beta, phi, f1, f2;
};

// Defines LIF with input signal
class LIFsig : public IF {
  public:
    
    struct signal_parameters sig;

    double drift(double v, double t) {
        return (this->mu - v + this->sig.eps*(this->sig.alpha*cos(2.0*M_PI*this->sig.f1*t) + this->sig.beta*cos(2.0*M_PI*this->sig.f2*t)));
    };
};


// runs a simulation N times which calculates the spike times
void simulation(neuron * neur, int N);

#endif // ifndef
