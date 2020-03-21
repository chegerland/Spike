//
// Created by cheg on 3/12/20.
//

#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("StepSignal constructors and calculation works", "[StepSignal]") {
  SECTION("Constructor from .json file"){
    StepSignal sig("../data/test_files/StepSignal_test.json");

    double t = 0.5;
    REQUIRE(sig.signal(t) == 0.0):

    t = 10.0;
    REQUIRE(sig.signal(t) == 3.0);
  };
}