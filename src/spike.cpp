#include <iostream>
#include <math.h>
#include <random>
#include "models.h"

//
//void pif() {
//  /* Parameters */
//  double t_0 = 0;
//  double t_end = 4;
//  int N = 1000;
//
//  double t;
//  double dt = (double) (t_end - t_0 ) / N;
//
//  double mu = 0.8;
//  double D = 0.2;
//
//  /* voltage array */
//  double v[N];
//  v[0] = 0;
//
//  /* random numbers */
//  //std::default_random_engine generator;
//  std::random_device rd{};
//  std::mt19937 generator{rd()};
//  std::normal_distribution<double> dist(0.0,sqrt(dt));
//
//  /* euler maruyama */
//  int i;
//  for (i = 0; i < N; i++) {
//    t = (i+1)*dt;
//    v[i+1] = v[i] + (mu)*dt + sqrt(2*D)*dist(generator);
//
//    /* reset rule */
//    if ( v[i+1] > 1) {
//      v[i+1] = 0;
//      std::cout << "FIRE" << std::endl;
//    }
////    std::cout << t << " " << v[i+1] << std::endl;
//  }
//};

int main(int argc, char *argv[]) {
  //pif();
  
  PIF P;
  P.t_0 = 0;
  P.t_end = 10;
  P.N = 1000;
  P.mu = 0.8;
  P.D = 0.1;

  em(P);
  
  return 0;
}
