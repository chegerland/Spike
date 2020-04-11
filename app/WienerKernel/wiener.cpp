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

  // get array for wiener kernel
  double *kernel;
  kernel = new double[time_frame.get_steps()];
  for (int i = 0; i < time_frame.get_steps(); i++) {
    kernel[i] = 0.;
  }

  // simulation parameters
  int N_sims = 1e5;

  // initialize progressbar
  ProgressBar progbar(N_sims, 70);
  progbar.display();

  // dummies
  const double T = time_frame.get_t_end() - time_frame.get_t_0();
  double norm = 1. / ((double)N_sims * T);

// loop over all neurons
#pragma omp parallel for
  for (int i = 0; i < N_sims; i++) {

    // construct white noise signal, spike train
    // SpikeTrain spike_train(time_frame.get_steps());
    WhiteNoiseSignal signal(input_file, time_frame);

    neuron.get_kernel(time_frame, signal, norm, kernel);

    // only one thread at a time shall increase the progress counter
#pragma omp critical
    ++progbar;
#pragma omp critical
    progbar.display();
  }

  // fourier transform wiener kernel to get susceptibility
  fftw_complex *suscept;
  suscept = new fftw_complex[time_frame.get_steps() / 2 + 1];

  fftw_plan p;
  p = fftw_plan_dft_r2c_1d((int)time_frame.get_steps(), kernel, suscept,
                           FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);

  // output
  std::ofstream file;
  file.open(opts.get_output_file());

  double scale = time_frame.get_dt();
  for (unsigned int i = 0; i < time_frame.get_steps(); i++) {
    file << time_frame.get_time(i) << "," << kernel[i];
    if (i < time_frame.get_steps() / 2 + 1) {
      file << "," << (double)i / (time_frame.get_t_end() - time_frame.get_t_0())
           << "," << scale * suscept[i][0] << "," << scale * suscept[i][1];
    }
    file << "\n";
  }

  delete[] kernel;
  file.close();
  progbar.done();
}
