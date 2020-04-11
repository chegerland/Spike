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
    REQUIRE(mean(signal.get_values(), time_frame.get_steps()) == Approx(0.0).margin(1e-13));
    REQUIRE(standard_deviation(signal.get_values(), time_frame.get_steps()) == Approx(2.0));
  }

  SECTION("Direct construction") {
    const TimeFrame time_frame(0.0, 1000.0, 1e-2);
    double alpha = 0.05;
    double f_low = 0.0;
    double f_high = 50.0;

    WhiteNoiseSignal signal(alpha, f_low, f_high, time_frame);

    // white noise should have standard deviation equal to alpha
    REQUIRE(mean(signal.get_values(), time_frame.get_steps()) == Approx(0.0).margin(1e-13));
    REQUIRE(standard_deviation(signal.get_values(), time_frame.get_steps()) == Approx(alpha));

  }
}
