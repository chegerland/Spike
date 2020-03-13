#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
#include <fstream>
#include <iostream>
#include <vector>

#include "ProgressBar.hpp"
#include "Spike.h"

// main
int main(int argc, char *argv[]) {

  // get file from command line
  Options opts(argc, argv);
  std::string input_file = opts.get_input_file();

  // define PIF neuron with adaptation and signal
  const PIF neuron(input_file);
  const ExpAdaptation adapt(input_file);

  // define simulation time frame
  const Timeframe time(input_file);

  // shortened time frame
  const double t_cut = 150.0;
  const Timeframe time_short(time.get_t_0(), time.get_t_end() - t_cut - time.get_t_0(), time.get_dt());
  const int cut_index = time.get_steps() - time_short.get_steps();

  // prepare susceptibility
  std::vector<double> frequencies;
  frequencies.resize(time_short.get_steps()/2 + 1);
  std::vector<std::complex<double>> suscept;
  suscept.resize(time_short.get_steps()/2 + 1);
  for (int i = 0; i < time_short.get_steps()/2 + 1; i++) {
    suscept[i] = 0.0;
  }

  // get firing rate
  const int N_sims = 1e4;
  const int N_sigs = 10;

  ProgressBar progbar(N_sigs, 70);

  std::cout << "Create white noise signal" << std::endl;
  WhiteNoiseSignal signal(input_file);

  for (int i = 0; i < N_sigs; i++) {

    std::cout << "Allocate firing rate" << std::endl;
    // define firing rate
    std::vector<double> rate;
    rate.resize(time.get_steps());
    for(int i = 0; i < time.get_steps(); i++) {
      rate[i] = 0.0;
    }


    // calculate firing rate
    std::cout << "Calculate firing rate" << std::endl;
#pragma omp parallel for
    for (int j = 0; j < N_sims; j++) {
      std::vector<bool> spike_train =
          neuron.get_spike_train(time, signal, adapt);
      add_to_firing_rate(spike_train, time, N_sims, rate);

// Progress
//#pragma omp critical
//      {
//        ++progbar;
//        progbar.display();
//      }
    }

    // shorten firing rate
    std::cout << "Shorten firing rate" << std::endl;
    std::vector<double> rate_short;
    rate_short.resize(time_short.get_steps());
    for(int j = 0; j < time_short.get_steps(); j++) {
      rate_short[j] = rate[cut_index + j];
    }

    std::cout << "Fourier transform firing rate" << std::endl;
    // calculate fourier transform of shortened firing rate
    std::vector<std::complex<double>> firing_rate_fourier;
    firing_rate_fourier.resize(time_short.get_steps()/2 + 1);
    fourier_trafo_firing_rate(rate_short, time_short, frequencies, firing_rate_fourier);

    std::cout << "Write to susceptibility" << std::endl;
    // fill susceptibility
    for (int j = 0; j < time_short.get_steps()/2 + 1; j++) {
      suscept[j] += 1./((double) N_sigs) * firing_rate_fourier[j];
    }

    ++progbar;
    progbar.display();
  }


  std::ofstream file;
  file.open("suscept.csv");

  for (unsigned int i = 0; i < time_short.get_steps()/2 + 1; i++) {
      file << frequencies[i] << "," << suscept[i].real() << "," << suscept[i].imag() << "\n";
  }

  progbar.done();
  file.close();

  return 0;
};

#pragma clang diagnostic pop