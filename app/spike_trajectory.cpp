#include <fstream>
#include <iostream>

#include "Spike/Spike.h"

using namespace Spike;

int main(int argc, char *argv[]) {

  // define time frame and neuron
  const TimeFrame tf(0.0, 30.0, 1e-3);
  LIFAC lifac(3.1, 0.0, 0.5, 1e-1);

  // define arrays for trajectory
  std::vector<double> v(tf.get_size());
  std::vector<double> a(tf.get_size());

  // calculate a trajectory
  lifac.get_voltage_curve(tf, v, a);

  // write trajectory to file
  std::ofstream file;
  file.open("../data/lifac_trajectory_no_noise.csv");
  file << "# Trajectory for the LIFAC\n";
  file << "# t, v, a\n";

  for (size_t i = 0; i < v.size(); i++) {
    file << tf.get_time(i) << "," << v[i] << "," << a[i] << std::endl;
  }

  file.close();

  return 0;
}