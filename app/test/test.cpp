#include "Spike.h"



int main(int argc, char *argv[]) {

  TimeFrame time(0., 500., 1e-3);

  // initial value for voltage
  double alpha = 0.03;
  double f_low = 0.0;
  double f_high = 500.;
  WhiteNoiseSignal signal(alpha, f_low, f_high, time);

  std::vector<double> spectrum;
  spectrum.resize(time.get_steps());
  power_spectrum(signal.get_values(), time, spectrum);

  for (double spec : spectrum) {
    std::cout << spec << std::endl;
  }

  return 0;
}