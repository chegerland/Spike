#include <iostream>

#include "Spike.h"

// main
int main(int argc, char *argv[])
{

  Options options(argc, argv);

  PIF pif(options.get_file());
  LIF lif(options.get_file());

  Timeframe time(0.0, 1000, 1e-3);

  int count_pif = pif.count(time);
  int count_lif = lif.count(time);


  std::cout << "time steps: " << time.get_steps() << std::endl;
  std::cout << "PIF counts: " << count_pif << std::endl;
  std::cout << "LIF counts: " << count_lif << std::endl;

  return 0;
};
