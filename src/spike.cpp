#include <iostream>
#include "factorial.h"

int main(int argc, char *argv[]){
   std::cout << "Hello World!" << std::endl;
   unsigned int fac = Factorial(5);
   printf("Factorial(5) = %d.\n", fac);
   return 0;
}
