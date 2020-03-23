#include <fftw3.h>
#include <random>

// json parser
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace pt = boost::property_tree;

#include "WhiteNoiseSignal.h"

// constructor from parameters
WhiteNoiseSignal::WhiteNoiseSignal(double alpha, double f_low, double f_high,
                                   const TimeFrame &time_frame)
    : Signal(time_frame), alpha(alpha), f_low(f_low), f_high(f_high){
  calculate_signal();
}

WhiteNoiseSignal::WhiteNoiseSignal(const std::string &input_file, const TimeFrame& time_frame)
    : Signal(time_frame) {
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
  calculate_signal();
}

void WhiteNoiseSignal::calculate_signal() {

  // set up rng
  std::random_device rd{};
  std::mt19937 generator{rd()};
  std::normal_distribution<double> dist(0.0, 1.0);

  const int steps = (int) time_frame.get_steps();
  const double dt = time_frame.get_dt();

  // define cut_off indices
  const int cut_low = (int)(f_low * steps * dt);
  const int cut_high = (int)(f_low * steps * dt);

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

  // allocate memory for the get_value
  double *signal;
  signal = (double *)malloc(steps * sizeof(double));

  // calculate get_value by fourier transforming from frequencies
  fftw_plan p;
  p = fftw_plan_dft_c2r_1d(steps, frequencies, signal, FFTW_ESTIMATE);
  fftw_execute(p);
  fftw_destroy_plan(p);
  fftw_free(frequencies);

  // normalize the get_value and copy into the vector
  const double scale = 1. / ((double)steps * dt);
  for (int i = 0; i < steps; i++) {
    this->signal_values[i] = scale * signal[i];
  }

  // free memory
  delete[] signal;
}

// return get_value
double WhiteNoiseSignal::signal(double t) const {
  // check if time is in time frame
  assert(t <= time_frame.get_t_end() && t >= time_frame.get_t_0());

  // calculate according index
  unsigned int index;
  index = (int)((t - time_frame.get_t_0()) / time_frame.get_dt());

  return signal_values[index];
}
