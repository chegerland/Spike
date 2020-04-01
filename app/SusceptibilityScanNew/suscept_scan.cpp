#include "../../extern/ProgressBar.hpp"
#include "Spike.h"
#include <fstream>

int main(int argc, char *argv[]) {

  // get file from command line
  Options opts(argc, argv);
  std::string input_file = opts.get_input_file();

  // construct objects
  const TimeFrame time_frame(input_file);
  const LIFAC neuron(input_file);


  // array for susceptibility, null entries
  fftw_complex *suscept;
  suscept = new fftw_complex[time_frame.get_steps() / 2 + 1];
  for (int i = 0; i < time_frame.get_steps() / 2; i++) {
    suscept[i][0] = 0.0;
    suscept[i][1] = 0.0;
  }

  // simulation parameters
  int N_sims = 2e5;

  // initialize progressbar
  ProgressBar progbar(N_sims, 70);
  progbar.display();

  // loop over all neurons
#pragma omp parallel for
  for (int i = 0; i < N_sims; i++) {

    // array for short temporary susceptibility, firing rate and signal
    fftw_complex *suscept_temp;
    suscept_temp = new fftw_complex[time_frame.get_steps() / 2 + 1];

    // construct a white noise signal, a spike train and a box firing rate
    WhiteNoiseSignal signal(input_file, time_frame);
    SpikeTrain spike_train(time_frame.get_steps());
    FiringRateBox firing_rate(time_frame);

    // get spike train
    neuron.get_spike_train(time_frame, signal, spike_train);
    firing_rate.add_spike_train(spike_train);

    // calculate firing rate
    firing_rate.calculate();

    // calculate susceptibility for this spike train
    susceptibility(signal.get_values(), firing_rate.get_values(), time_frame,
                   suscept_temp);

    // add susceptibility of the spike train to overall susceptibility
    for (int i = 0; i < time_frame.get_steps() / 2; i++) {
      suscept[i][0] += 1. / ((double)N_sims) * suscept_temp[i][0];
      suscept[i][1] += 1. / ((double)N_sims) * suscept_temp[i][1];
    }

    // free memory
    delete [] suscept_temp;

    // only one thread at a time shall increase the progress counter
#pragma omp critical
    ++progbar;
#pragma omp critical
    progbar.display();
  }

  // output
  std::ofstream file;
  file.open(opts.get_output_file());

  for (unsigned int i = 0; i < time_frame.get_steps() / 2; i++) {
    file << (double)i /
                (time_frame.get_t_end() - time_frame.get_t_0())
         << "," << suscept[i][0] << "," << suscept[i][1] << "\n";
  }

  file.close();
  progbar.done();
}