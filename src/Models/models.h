#ifndef MODELS_H
#define MODELS_H

#include <math.h>
#include <vector>

/*
  Defines the integrate and fire (IF) neuron, defaults to perfect IF
*/
class IF {
  /* 
   bla bla
  */
  public:
    /* constructor */
    IF() {};

    /*! Simulation parameters
      */
    int N;
    double t_0, t_end;
    double mu, D;
    
    /* parameter for signal */
    double eps;
    double f;

    /*!
      drift and diffusion functions,  can be overwritten by subclasses 
      */
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
    /* constructor */
    LIFsig() {};

    /*!
      change the drift 
      */
    double drift(double v, double t) {
      return (this->mu - v + this->eps*cos(2.0*3.14159265*this->f*t));
    };
};


/* functions */
void voltage_curve(IF* neuron, std::vector<double> &t, std::vector<double> &v);
void spike_times(IF* neuron, std::vector<double> &spikes);
void spike_train(IF* neuron, std::vector<double> &spikes);
double firing_rate(double t, const std::vector<double> &spikeTimes, double dt);

#endif // ifndef
