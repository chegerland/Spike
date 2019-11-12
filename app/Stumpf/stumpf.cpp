#include <math.h>
#include <random>
#include <iostream>

// main
int main(int argc, char *argv[])
{
  // number of neurons
  int N = 100000;

  // neuron parameters
  double mu = 1.1;
  double D = 1e-3;

  // adaption
  double Delta = 3;
  double tau_a = 0.1;

  // signal parameters
  double eps = 0.05;
  double alpha = 1.0;
  double f1 = 0.215;

  // parameters
  double t_0 = 0.0;
  double t_end = 70.0;
  double dt = 1e-2;
  int Nsteps = (int) (t_end - t_0)/dt;

  // rng
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(dt));

  int *trains = new int[N*Nsteps];

  for ( int i = 0; i < N; i++)
  {
    // initial values
    double v = 0.0;
    double t = t_0;
    double a = 0;

    // euler maruyama scheme
    for (int j = 0; j < Nsteps; j++)
    {
      // update time and voltage
      t += dt ;
      //v += (mu - v) * dt + eps*alpha*cos(2.0 * M_PI * f1 * t) * dt +  sqrt(2.0 * D)* dist(generator);
      v += (mu - v) * dt - a*dt + eps*alpha*cos(2.0 * M_PI * f1 * t) * dt +  sqrt(2.0 * D)* dist(generator);
      a += 1.0/tau_a *( -a)*dt;

      // fire and reset rule
      if (v > 1)
      {
        v = 0;
        a += Delta;
        trains[i*Nsteps + j] = 1;
      }
      else
      {
        trains[i*Nsteps + j] = 0;
      };

    };

  };

  double rate[Nsteps];
  for (int k = 0; k < Nsteps; k++)
  {
    for (int l = 0; l < N; l++)
    {
      rate[k] += 1.0/( N *dt ) *  (double) trains[l*Nsteps + k];
    };
    std::cout << rate[k] << std::endl;
  };

  delete[] trains;

  exit(0);
};
