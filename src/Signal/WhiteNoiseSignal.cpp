#include <fftw3.h>
#include <random>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <utility>
#include <iostream>

namespace pt = boost::property_tree;

#include "WhiteNoiseSignal.h"

// constructor from parameters
WhiteNoiseSignal::WhiteNoiseSignal(double alpha, double f_low, double f_high, Timeframe time)
    : alpha(alpha), f_low(f_low), f_high(f_high), time(std::move(time)) {
  // generate the white noise
  generate_white_noise();
}

WhiteNoiseSignal::WhiteNoiseSignal(const std::string &input_file) : time(input_file) {
  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  auto type = root.get<std::string>("Signal.type");
  assert(type == "white noise");

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  f_low = root.get<double>("Signal.f_low");
  f_high = root.get<double>("Signal.f_high");
  assert(f_high > f_low);

  // generate the white noise
  generate_white_noise();
}

void WhiteNoiseSignal::generate_white_noise() {

  // set up rng
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, 1.0);

  // length of the signal
  const unsigned int steps = time.get_steps();
  this->signal_values.resize(steps);

  // define cut_off indeces
  //const int cut_low = (int)(f_low * (time.get_t_end() - time.get_t_0()));
  const int cut_low = (int)(f_low * time.get_steps() * time.get_dt());
  //const int cut_high = (int)(f_high * (time.get_t_end() - time.get_t_0()));
  const int cut_high = (int)(f_low * time.get_steps() * time.get_dt());

  // frequencies space
  fftw_complex *frequencies;
  frequencies =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * (steps / 2 + 1));


  // white noise in frequency space has constant amplitude, random phase
  double rand;
  for (int i = 1; i < steps / 2; i++) {
    rand = dist(generator);
    frequencies[i][0] = cos(2.0 * M_PI * rand);
    frequencies[i][1] = sin(2.0 * M_PI * rand);

    // cut frequencies
    if (i < cut_low) {
      frequencies[i][0] = 0.0;
      frequencies[i][1] = 0.0;
    }

    if (i > cut_high) {
      frequencies[i][0] = 0.0;
      frequencies[i][1] = 0.0;
    }
  }

  // DC and Nyquist frequency have to be purely real
  frequencies[0][0] = 1.0;
  frequencies[0][1] = 0.0;
  frequencies[steps / 2 + 1][0] = 1.0;
  frequencies[steps / 2 + 1][1] = 0.0;

  // allocate memory for the signal
  double *signal;
  signal = (double *)malloc(steps * sizeof(double));

  // calculate signal by fourier transforming from frequencies
  fftw_plan p;
  p = fftw_plan_dft_c2r_1d(steps, frequencies, signal, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  fftw_free(frequencies);

  // normalize the signal and copy into the vector
  const double scale = 1. / ((double)steps * time.get_dt());
  for (int i = 0; i < steps; i++) {
    this->signal_values[i] = scale * signal[i];
  }

  // free memory
  delete[] signal;
}

// update white noise signal
void WhiteNoiseSignal::update() {
  // clear the signal values
  this->signal_values.clear();

  // generate white noise again
  generate_white_noise();
}

// return signal
double WhiteNoiseSignal::signal(double t) const {
  // check if time is in time frame
  assert(t <= time.get_t_end() && t >= time.get_t_0());

  // calculate according index
  unsigned int index;
  index = (int)((t - time.get_t_0()) / time.get_dt());

  return signal_values[index];
};
