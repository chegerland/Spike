#ifndef MODELS_H
#define MODELS_H

#include <math.h>
#include <vector>

/*!
  Defines the integrate and fire (IF) neuron, defaults to perfect IF
*/
class IF {
  public:
    // constructor
    IF() {};

    // Simulation parameters
    int N;
    double t_0, t_end;
    double mu, D;

    // drift and diffusion functions,  can be overwritten by subclasses 
    virtual double drift(double v, double t) {
      return this->mu;
    };
    virtual double diffusion(double v, double t) {
      return sqrt(2*this->D);
    };
};

/*! 
  Defines leaky integrate and fire neuron, inherits everything from IF
*/
class LIF : public IF {
  public:
    /* constructor */
    LIF() {};

    /*!
      change the drift 
      */
    double drift(double v, double t) {
      return (this->mu - v);
    };
};

/*! 
  Defines leaky integrate and fire neuron, inherits everything from IF
*/
class LIFsig : public IF {
  public:
    LIFsig(){};
    ~LIFsig(){};

    /* parameter for signal */
    double eps = 0;
    double alpha = 0;
    double beta = 0;
    double phi = 0;
    double f1 = 0;
    double f2 = 0;

    /*!
      change the drift 
      */
    double drift(double v, double t) {
        return (this->mu - v + this->eps*(this->alpha*cos(2.0*3.14159265*this->f1*t) + this->beta*cos(2.0*3.14159265*this->f2*t)));
      //if (t < 0) {
      //  return (this->mu - v);
      //} else {
      //  return (this->mu - v + 0.01*t*this->eps*(this->alpha*cos(2.0*3.14159265*this->f1*t) + this->beta*cos(2.0*3.14159265*this->f2*t)));
      //};
    };
};


/* functions */
void voltage_curve(IF* neuron, std::vector<double> &t, std::vector<double> &v);
void spike_times(IF* neuron, std::vector<double> &spikes);
void spike_train(IF* neuron, std::vector<double> &spikes);
double firing_rate(double t, const std::vector<double> &spikeTimes, double dt);

#endif // ifndef
