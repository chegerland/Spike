#include <math.h>
#include <random>
#include <iostream>
#include <fstream>
#include "models.h"


/* Euler Maruyama
* - with fire and reset rule
* - without refractory time
* - returns time discretization and voltage 
*/
void em(IF* neuron, double t[], double v[]) {

  /* initial values*/
  v[0] = 0;
  t[0] = neuron->t_0;

  /* time step */
  double dt = (double) (neuron->t_end - neuron->t_0 ) / neuron->N;

  /* random numbers */
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0,sqrt(dt));

  /* euler maruyama */
  for (int i = 0; i < neuron->N - 1; i++) {
    t[i+1] = t[i] + dt;
    v[i+1] = v[i] + neuron->drift(v[i],t[i])*dt + neuron->diffusion(v[i],t[i])*dist(generator);

    /* reset rule */
    if ( v[i+1] > 1) {
      v[i+1] = 0;
    }
  }
};

/* calculates the voltage curve for a given neuron 
* - prints the time and voltage array into a given file name
*/
void curveToFile(IF *neuron, char fileName[100]) {
  /* define vectors to put voltage curve in */
  double t[neuron->N];
  double v[neuron->N];

  /* calculate voltage curve */
  em(neuron, t, v);

  /* writes values to file */
  std::ofstream file;
  file.open(fileName);
  file << "t,v" << "\n";

  /* print values to file */
  for (int i = 0; i < neuron->N; i++) {
    file << t[i] << "," << v[i] << "\n";
  }

  /* close file */
  file.close();
};


/* output to standard output */
void curveToStdOut(IF *neuron) {
  /* define vectors to put voltage curve in */
  double t[neuron->N];
  double v[neuron->N];

  /* calculate voltage curve */
  em(neuron, t, v);

  /* print values to file */
  for (int i = 0; i < neuron->N; i++) {
    std::cout << t[i] << " " << v[i] << std::endl;
  }
};