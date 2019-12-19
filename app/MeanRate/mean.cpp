#include <iostream>

#include "Spike.h"

// main
int main(int argc, char *argv[])
{

  Options *options;
  options = new Options(argc, argv);

  PIF pif(options->file);
  LIF lif(options->file);

  Timeframe time(0.0, 5.0, 1e-2);

  int count_pif = pif.count(&time);
  int count_lif = lif.count(&time);

  std::cout << "PIF counts: " << count_pif << std::endl;
  std::cout << "LIF counts: " << count_lif << std::endl;

  return 0;
};
