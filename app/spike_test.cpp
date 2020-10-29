#include <iostream>

#include "Spike/Spike.h"

using namespace Spike;

int main(int argc, char *argv[]) {

  TimeFrame tf(0, 300, 5e-3);

  std::vector<std::vector<std::complex<double>>> array(tf.get_size()/4);

  for (size_t i = 0; i < array.size(); i++) {
    array[i].resize(array.size() - i);
  }

  std::cout << tf.get_size() << std::endl;
  std::cout << tf.get_size()/4 << std::endl;
  std::cout << (tf.get_size()/4 + 1) * (tf.get_size()/4) /2 << std::endl;

  size_t count = 0.;
  for (size_t i = 0; i < array.size(); i++) {
    for (size_t j = 0; j < array.size() - i; j++) {
      array[i][j] = count;
      count++;
    }
  }

  for (size_t i = 0; i < array.size(); i++) {
    for (size_t j = 0; j < array.size() - i; j++) {
      std::cout << array[i][j] << " ";
    }
    std::cout << std::endl;
  }


  return 0;
}