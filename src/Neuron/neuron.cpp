#include <iostream>
#include <fstream>
#include <random>

#include "neuron.h"

/*!
 * SHOULD Return the voltage curve of a single neuron simulation.
 */
void IF::voltage_curve() const
{
  std::cout << "D = " << this->D << std::endl;
  std::cout << "mu = " << this->mu << std::endl;
};

// get spike times of an IF neuron
void IF::spike_times(std::vector<double> &spikes) const
{
  double v = 0;
  double t = this->t_0;

  // random numbers
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, sqrt(this->dt));

  // euler maruyama scheme
  double next_step = 0;

  while (t < t_end)
  {
    t += dt;
    next_step = v + this->drift(v, t) * this->dt + this->diffusion(v, t) * dist(generator);

    if (v > 1) {
      v = 0;
      spikes.push_back(t);
    }
    else {
      v = next_step;
    }
  };
};

// simulate a neuron N times, put spike times into output file
void Neuron::simulation(Files *files, int N) const
{
  std::vector<double> spikes; // vector to store spike times in

  // open filestream
  std::ofstream file;
  file.open(files->output_file);

  // run N simulations
  for (int i = 0; i < N; i++)
  {
    this->spike_times(spikes); // get spike times

    // loop over of entry in spikes times
    for (int i = 0; i < spikes.size(); i++)
    {
      file << spikes[i] << " ";
    };

    // clear spike times vector and start new line in the file
    spikes.clear();
    file << "\n";
  }

  file.close(); // close file stream
};
