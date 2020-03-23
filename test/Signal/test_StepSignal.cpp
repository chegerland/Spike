#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("StepSignal constructors and calculation works", "[StepSignal]") {
  SECTION("Constructor from .json file"){
    const std::string file = "../data/test_files/StepSignal_test.json";
    const TimeFrame time_frame(file);

    StepSignal sig(file, time_frame);

    double t = 0.5;
    REQUIRE(sig.signal(t) == 0.0);

    t = 10.0;
    REQUIRE(sig.signal(t) == 3.0);
  }
}