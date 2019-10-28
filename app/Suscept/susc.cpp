#include <iostream>
#include <math.h>

#ifdef __cplusplus
extern "C"
{
  #endif

  /* with slight change from https://stackoverflow.com/questions/11579367/implementation-of-goertzel-algorithm-in-c */
  double goertzel_mag(int numSamples,int TARGET_FREQUENCY,int SAMPLING_RATE, double* data)
  {
    int      k,i;
    double   doublenumSamples;
    double   omega,sine,cosine,coeff,q0,q1,q2,magnitude,real,imag;

    double   scalingFactor = numSamples / 2.0;

    doublenumSamples = (double) numSamples;
    k = (int) (0.5 + ((doublenumSamples * TARGET_FREQUENCY) / SAMPLING_RATE));
    omega = (2.0 * M_PI * k) / doublenumSamples;
    sine = sin(omega);
    cosine = cos(omega);
    coeff = 2.0 * cosine;
    q0=0;
    q1=0;
    q2=0;

    for(i=0; i<numSamples; i++)
    {
      q0 = coeff * q1 - q2 + data[i];
      q2 = q1;
      q1 = q0;
    }

    // calculate the real and imaginary results
    // scaling appropriately
    real = (q1 - q2 * cosine) / scalingFactor;
    imag = (q2 * sine) / scalingFactor;

    magnitude = sqrtf(real*real + imag*imag);
    return magnitude;
  }

  #ifdef __cplusplus
}
#endif


int main(int argc, char *argv[])
{
  int N = 3;
  double rate[N] = {2.0, 3.0, 4.0};

  double test = goertzel_mag(N, 1.3, 0.01, rate);
  std::cout << test << std::endl;
  return 0;
};
