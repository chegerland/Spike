#include <iostream>
#include <fstream>
#include <vector>

#include "neuron.h"

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
