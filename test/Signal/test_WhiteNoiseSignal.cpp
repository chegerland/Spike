#include "../../extern/catch/catch.hpp"
#include "Spike.h"
#include <iostream>

TEST_CASE("White noise constructors work") {
  SECTION("Constructor from .json file") {
    const std::string file = "../data/test_files/WhiteNoiseSignal_test.json";
    const TimeFrame time_frame(file);
    WhiteNoiseSignal signal(file, time_frame);

    REQUIRE(signal.signal(3.5) < 20);

    // white noise should have standard deviation equal to alpha
    REQUIRE(mean(signal.get_values(), time_frame.get_steps()) ==
            Approx(0.0).margin(1e-13));
    // REQUIRE(standard_deviation(signal.get_values(), time_frame.get_steps())
    // ==
    //        Approx(2.0));
  }

  SECTION("Direct construction") {
    const TimeFrame time_frame(0.0, 1000.0, 1e-2);
    double alpha = 0.07;
    double f_low = 0.0;
    double f_high = 50.0;

    WhiteNoiseSignal signal(alpha, f_low, f_high, time_frame);

    // white noise should have standard deviation equal to alpha
    REQUIRE(mean(signal.get_values(), time_frame.get_steps()) ==
            Approx(0.0).margin(1e-13));
    REQUIRE(standard_deviation(signal.get_values(), time_frame.get_steps()) ==
            Approx(sqrt(alpha * 2. * (f_high - f_low))));
  }
}

TEST_CASE("White Noise power spectrum") {
  const TimeFrame time_frame(0.0, 500.0, 1e-2);
  double alpha = 0.3;
  double f_low = 0.0;
  double f_high = 50.0;

  WhiteNoiseSignal signal(alpha, f_low, f_high, time_frame);

  std::vector<double> spectrum;
  spectrum.resize(time_frame.get_steps() / 2);

  power_spectrum(signal.get_values(), time_frame, spectrum);

  // height of the spectrum should be alpha (in the non-cut-off regime)
  for (size_t i = 1; i < spectrum.size() - 1; i++) {
    REQUIRE(spectrum[i] * (time_frame.get_t_end() - time_frame.get_t_0()) ==
            Approx(alpha));
  }
}
