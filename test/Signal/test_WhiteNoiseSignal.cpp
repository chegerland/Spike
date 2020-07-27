#include "../../extern/catch/catch.hpp"
#include "Spike.h"
#include <iostream>

TEST_CASE("White noise constructors work") {
  SECTION("Constructor from .json file") {
    const std::string file = "../data/test_files/WhiteNoiseSignal_test.ini";
    const TimeFrame time_frame(file);
    WhiteNoiseSignal signal(file, time_frame);

    REQUIRE(signal.signal(3.5) < 20);

    // white noise should have standard deviation equal to alpha
 //   REQUIRE(mean(signal.get_values()) == Approx(0.0).margin(1e-13));
  }

  SECTION("Direct construction") {
    const TimeFrame time_frame(0.0, 5000.0, 1e-3);
    double alpha = 0.07;
    double f_low = 0.0;
    double f_high = 500.0;

    WhiteNoiseSignal signal(alpha, f_low, f_high, time_frame);

    // white noise should have standard deviation equal to alpha
//    REQUIRE(mean(signal.get_values()) == Approx(0.0).margin(1e-13));
    REQUIRE(standard_deviation(signal.get_values()) ==
            Approx(2.*sqrt(alpha *(f_high - f_low))));
  }
}

TEST_CASE("White Noise power spectrum") {
  const TimeFrame time_frame(0.0, 500.0, 1e-2);
  double alpha = 0.3;
  double f_low = 0.0;
  double f_high = 50.0;

  WhiteNoiseSignal signal(alpha, f_low, f_high, time_frame);

  std::vector<double> spectrum(time_frame.get_size() / 2 + 1);

  power_spectrum(signal.get_values(), time_frame, spectrum);

  // height of the spectrum should be alpha (in the non-cut-off regime)
  for (size_t i = 1; i < spectrum.size() - 1; i++) {
    REQUIRE(spectrum[i] == Approx(2. * alpha));
  }
}
