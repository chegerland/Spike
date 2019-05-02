#ifndef MODELS_H
#define MODELS_H

class Simulation {
  public:
    double t_0, t_end;
    int N;
};


class PIF: public Simulation {
  public:
    double mu, D;
    double drift(double, double);
    double diffusion(double, double);
    friend void em(PIF pif);
};

double PIF::drift(double v, double t) {
  return this->mu;
};

double PIF::diffusion(double v, double t) {
  return sqrt(2*this->D);
};

void em(PIF pif) {
  double t;
  double dt = (double) (pif.t_end - pif.t_0 ) / pif.N;

  /* voltage array */
  double v[pif.N];
  v[0] = 0;

  /* random numbers */
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0,sqrt(dt));

  /* euler maruyama */
  int i;
  for (i = 0; i < pif.N; i++) {
    t = (i+1)*dt;
    v[i+1] = v[i] + pif.drift(v[i],t)*dt + pif.diffusion(v[i],t)*dist(generator);

    /* reset rule */
    if ( v[i+1] > 1) {
      v[i+1] = 0;
      std::cout << "FIRE" << std::endl;
    }
  }
};

#endif // ifndef
