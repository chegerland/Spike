#include "Spike.h"



int main(int argc, char *argv[]) {

  LIFAC lif(3.0, 5.0, 10.5, 30*4.55);
  TimeFrame tf(0, 10, 0.1);
  WhiteNoiseSignal signal(5.0, 10, 20, tf);

  std::cout << lif << std::endl;
  std::cout << tf << std::endl;
  std::cout << signal << std::endl;

  return 0;
}