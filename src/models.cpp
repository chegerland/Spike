#include <iostream>
#include <fstream>
#include <math.h>
#include <random>
#include "models.h"

double PIF::drift(double v, double t) {
  return this->mu;
};

double PIF::diffusion(double v, double t) {
  return sqrt(2*this->D);
};

/* Euler Maruyama */
void em(double v[], PIF pif) {
  double t;
  double dt = (double) (pif.t_end - pif.t_0 ) / pif.N;

  std::ofstream file;
  file.open("../data/pif.csv");
  file << "t,v" << "\n";

/* voltage array */
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
    }

    //std::cout << t << " " << v[i+1] << std::endl;
    file << t << "," << v[i+1] << "\n";
  }

  file.close();
};
