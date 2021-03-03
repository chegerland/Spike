# Getting started {#getting_started}

In this short guide we will install Spike and show you a small calculation that you can do with it.


# Installing spike
1. Clone the repository 
```
git clone https://github.com/chegerland/Spike.git
```
2. Make a build folder and build 
```
mkdir -p build && cd build
cmake .. && make
```

# Your first calculation
Spike is both a library and a bunch of executables.
You can use every part of the library to build your own programs, e.g. take a look at the following program:
~~~~{.cpp}
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
  file.open("trajectory.csv");
  file << "# Trajectory for the LIFAC\n";
  file << "# t, v, a\n";

  for (size_t i = 0; i < v.size(); i++) {
    file << tf.get_time(i) << "," << v[i] << "," << a[i] << std::endl;
  }

  file.close();

  return 0;
}
~~~~
Here we calculate the trajectory of a leaky integrate-and-fire neuron with spike-frequency adaptation and save it to a file.
This executable may also be found in `app/spike_trajectory.cpp`.

# Working with the Spike apps
In `app/` you can find programs that I have written for my master thesis.
Most of them are intended to be used on a computing cluster using MPI.
Every simulation takes a `.ini` file as an input argument, runs the simulation and produces an according `.csv` output file.
As an example, if we want to calculate the linear susceptibility of a leaky integrate-and-fire neuron, we would need an input file like this and put it in `data/lif.ini`
~~~~{.ini}
[TimeFrame]
t_0 = 0.0
t_end = 1000.0
dt = 5e-4

[Neuron]
type = LIF
mu = 2.0
D = 1e-1

[Simulation]
c = 1.0
N_neurons = 10000
~~~~
We have defined all parameters and may use the executable `bin/spike_suscept` in parallel by running
```
mpirun -np 4 bin/spike_suscept -f data/lif.ini
```
This uses four processes in parallel and the output file `data/lif_suscept_lin.csv` contains two columns: the first one being the frequencies and the second one being the complex value of the linear susceptibility at that frequency.



