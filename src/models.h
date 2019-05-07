#ifndef MODELS_H
#define MODELS_H

#include <math.h>
#include <vector>

/* IF Class
 * - defines the integrate and fire neuron
 * - defaults to perfect integrate and fire neuron
 */
class IF {
  public:
    /* constructor */
    IF() {};

    /* parameters */
    int N;
    double t_0, t_end;
    double mu, D;

    /* drift and diffusion function */
    /* can be overwritten by subclasses */
    virtual double drift(double v, double t) {
      return this->mu;
    };
    virtual double diffusion(double v, double t) {
      return sqrt(2*this->D);
    };
};

/* LIF */
class LIF : public IF {
  public:
    /* constructor */
    LIF() {};

    /* change the drift */
    double drift(double v, double t) {
      return (this->mu -v);
    };
};


/* voltage curve */
void em(IF* neuron, double t[], double v[]);

void curveToFile(IF *neuron, char fileName[100]);
void curveToStdOut(IF *neuron);
#endif // ifndef