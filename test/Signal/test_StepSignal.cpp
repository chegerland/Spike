#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("StepSignal constructors and calculation works", "[StepSignal]") {
  SECTION("Constructor from .json file") {
    const std::string file = "../data/test_files/StepSignal_test.json";
    const TimeFrame time_frame(file);

    StepSignal sig(file, time_frame);

    REQUIRE(sig.signal(0.5) == 0.0);
    REQUIRE(sig.signal(10.0) == 3.0);
  }

  SECTION("Direct constructor") {
    const TimeFrame time_frame(0.0, 10.0, 0.1);
    double alpha = 3.5;
    double t_0 = 4.;
    StepSignal signal(alpha, t_0, time_frame);

    REQUIRE(signal.signal(5.) == 3.5);
    REQUIRE(signal.signal(3.9) == 0.0);
  }
}

TEST_CASE("Step Signal value array is computed correctly") {

  const TimeFrame time_frame(0.0, 10.0, 0.1);
  double alpha = 3.5;
  double t_0 = 4.;
  StepSignal signal(alpha, t_0, time_frame);

  for (unsigned int i = 0; i < time_frame.get_steps(); i++) {
    if (time_frame.get_time(i) < t_0) {
      REQUIRE(signal.get_value(i) == 0);
    } else {
      REQUIRE(signal.get_value(i) == alpha);
    }
  }
}