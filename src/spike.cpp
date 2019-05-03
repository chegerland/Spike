#include "models.h"
#include <iostream>

int main(int argc, char *argv[]) {
  
  PIF P;
  P.t_0 = 0;
  P.t_end = 17;
  P.N = 1000;
  P.mu = 0.3;
  P.D = 0.1;

  double v[P.N];

  em(v, P);

  std::cout << v[5] << std::endl;
  
  return 0;
}
