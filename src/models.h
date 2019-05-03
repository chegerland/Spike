#ifndef MODELS_H
#define MODELS_H

/* Simulation class
 * - defines simulation parameters
 */
class Simulation {
  public:
    double t_0, t_end;
    int N;
};

/* PIF Class
 * defines th eperfect integrate and fire neuron
 */
class PIF: public Simulation {
  public:
    double mu, D;
    double drift(double, double);
    double diffusion(double, double);
    friend void em(double v[], PIF pif);
};

#endif // ifndef
