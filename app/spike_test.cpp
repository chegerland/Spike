#include <iostream>

#include "Spike/Spike.h"

using namespace Spike;

int main(int argc, char *argv[]) {

  TimeFrame tf(0, 300, 5e-3);
  WhiteNoiseSignal signal(0.742, 0.0, 1.0/(2. * tf.get_dt()), tf);

  const std::vector<std::complex<double>> &isf = signal.get_frequencies();

  for (auto i : isf) {
    std::cout << std::abs(i)*std::abs(i) << std::endl;
  }
  std::cout << 2.*signal.get_alpha()*300 << std::endl;



  return 0;
}