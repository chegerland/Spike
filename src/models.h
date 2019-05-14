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
void voltageCurve(IF* neuron, std::vector<double> &t, std::vector<double> &v);
void spikeTimes(IF* neuron, std::vector<double> &spikes);
void spikeTrain(IF* neuron, std::vector<double> &spikes);

void toStdOut(const std::vector<double> &x, const std::vector<double> &y);
void toFile(char fileName[100], const std::vector<double> &x, const std::vector<double> &y);

double firingRate(double t, const std::vector<double> &spikeTimes, double dt);


#endif // ifndef