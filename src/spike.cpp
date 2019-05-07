#include "models.h"
#include <iostream>
#include <fstream>
#include <vector>


int main(int argc, char *argv[])
{

  // define new neuron with all parameters
  IF *P = new LIF();
  P->t_0 = 4;
  P->t_end = 17;
  P->N = 1000;
  P->mu = 0.8;
  P->D = 0.01;

  //char fileName[100] = "../data/test.csv";
  //curveToFile(P, fileName);
  curveToStdOut(P);


return 0;
}
