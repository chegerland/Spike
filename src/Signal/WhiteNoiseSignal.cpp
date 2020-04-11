#include <fftw3.h>

// json parser
#include <Spike.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

namespace pt = boost::property_tree;

#include "WhiteNoiseSignal.h"

// constructor from parameters
WhiteNoiseSignal::WhiteNoiseSignal(double alpha, double f_low, double f_high,
                                   const TimeFrame &time_frame)
    : Signal(time_frame), alpha(alpha), f_low(f_low), f_high(f_high),
      generator(rd()), dist(0.0, 1.0) {
  calculate_signal();
}

WhiteNoiseSignal::WhiteNoiseSignal(const std::string &input_file,
                                   const TimeFrame &time_frame)
    : Signal(time_frame), generator(rd()), dist(0.0, 1.0) {
  pt::ptree root;
  pt::read_json(input_file, root);

  // check if type is right
  auto type = root.get<std::string>("Signal.type");
  assert(type == "white noise");

  // read simulation data into simulation variables
  alpha = root.get<double>("Signal.alpha");
  f_low = root.get<double>("Signal.f_low");
  f_high = root.get<double>("Signal.f_high");
  assert(f_high > f_low && f_low >= 0.);

  // generate the white noise
  calculate_signal();
}

void WhiteNoiseSignal::calculate_signal() {

  size_t steps = time_frame.get_steps();
  const double dt = time_frame.get_dt();

  // define cut_off indices
  size_t cut_low = f_low * steps * dt;
  size_t cut_high = f_high * steps * dt;

  // frequencies space
  std::vector<std::complex<double>> frequencies;
  frequencies.resize(steps / 2 + 1);

  // white noise in frequency space has constant amplitude, random phase
  double rand;
  for (size_t i = 1; i < steps / 2; i++) {
    rand = dist(generator);
    frequencies[i] = {cos(2.0 * M_PI * rand), sin(2.0 * M_PI * rand)};

    // cut frequencies
    if (i < cut_low || i > cut_high) {
      frequencies[i] = 0.0;
    }
  }

  // DC and Nyquist frequency have to be purely real
  frequencies[0] = 1.0;
  frequencies[steps / 2] = 1.0;

  // calculate get_value by fourier transforming from frequencies
  fftw_plan p;
#pragma omp critical
  p = fftw_plan_dft_c2r_1d(steps,
                           reinterpret_cast<fftw_complex *>(frequencies.data()),
                           this->signal_values.data(), FFTW_ESTIMATE);

  fftw_execute(p);

#pragma omp critical
  fftw_destroy_plan(p);

  // normalize the get_value and copy into the vector
  const double scale = 1. / ((double)steps * dt);
  for (size_t i = 0; i < steps; i++) {
    signal_values[i] = scale * signal_values[i];
  }

  // normalize signal with its own standard deviation and multiply by alpha, so
  // that we have new standard variation equal to 1
  double standard_dev = standard_deviation(signal_values, steps);
  double mean_val = mean(signal_values, steps);

  for (size_t i = 0; i < steps; i++) {
    signal_values[i] =
        this->alpha / (standard_dev) * (signal_values[i] - mean_val);
  }
}

// return get_value
double WhiteNoiseSignal::signal(double t) const {
  // check if time is in time frame
  assert(t <= time_frame.get_t_end() && t >= time_frame.get_t_0());

  // calculate according index
  size_t index;
  index = (size_t)((t - time_frame.get_t_0()) / time_frame.get_dt());

  return signal_values[index];
}

void WhiteNoiseSignal::print_info(std::ofstream &file) {
  file << "# Signal parameters: "
       << "\n"
       << "# type = "
       << "white noise"
       << "\n"
       << "# alpha = " << alpha << "\n"
       << "# f_low = " << f_low << "\n"
       << "# f_high = " << f_high << "\n";
}
