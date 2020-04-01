#include "../../extern/ProgressBar.hpp"
#include "Spike.h"
#include <fstream>

int main(int argc, char *argv[]) {

  // get file from command line
  Options opts(argc, argv);
  std::string input_file = opts.get_input_file();

  // construct objects
  TimeFrame time_frame(input_file);
  TimeFrame time_frame_short(time_frame.get_t_0() + 100.,
                                 time_frame.get_t_end(), time_frame.get_dt());
  WhiteNoiseSignal signal(input_file, time_frame);
  LIFAC neuron(input_file);
  SpikeTrain spike_train(time_frame.get_steps());
  FiringRateBox firing_rate(time_frame);

  // array for susceptibility, null entries
  fftw_complex *suscept;
  suscept = new fftw_complex[time_frame_short.get_steps() / 2 + 1];
  for (int i = 0; i < time_frame_short.get_steps() / 2; i++) {
    suscept[i][0] = 0.0;
    suscept[i][1] = 0.0;
  }

  // array for short temporary susceptibility, firing rate and signal
  fftw_complex *suscept_temp;
  suscept_temp = new fftw_complex[time_frame_short.get_steps() / 2 + 1];
  double *firing_rate_short;
  firing_rate_short = new double[time_frame_short.get_steps()];
  double *signal_short;
  signal_short = new double[time_frame_short.get_steps()];

  // simulation parameters
  int N_sims = 1e5;
  int N_sigs = 10;

  // progressbar
  ProgressBar progbar(N_sigs, 70);
  progbar.display();

  for (int j = 0; j < N_sigs; j++) {
#pragma omp parallel for
    for (int i = 0; i < N_sims; i++) {
      // add spike trains to firing rate
      neuron.get_spike_train(time_frame, signal, spike_train);
      firing_rate.add_spike_train(spike_train);
      spike_train.clear();
    }

    // calculate the firing rate
    firing_rate.calculate();

    // shorten firing rate and signal
    shorten_array(firing_rate.get_values(), time_frame, time_frame_short,
                  firing_rate_short);
    shorten_array(signal.get_values(), time_frame, time_frame_short,
                  signal_short);

    // calculate susceptibility
    susceptibility(signal_short, firing_rate_short, time_frame_short,
                   suscept_temp);

    for (int i = 0; i < time_frame_short.get_steps() / 2; i++) {
      suscept[i][0] += 1. / ((double)N_sigs) * suscept_temp[i][0];
      suscept[i][1] += 1. / ((double)N_sigs) * suscept_temp[i][1];
    }

    // clear firing rate
    firing_rate.clear();

    // progress
    ++progbar;
    progbar.display();
  }

  // output
  std::ofstream file;
  file.open(opts.get_output_file());

  for (unsigned int i = 0; i < time_frame_short.get_steps() / 2; i++) {
    file << (double)i / (time_frame_short.get_t_end() - time_frame_short.get_t_0()) << ","
         << suscept[i][0] << "," << suscept[i][1] << "\n";
  }

  file.close();
  progbar.done();

}