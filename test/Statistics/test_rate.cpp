#include "catch.hpp"
#include <math.h>

#include "statistics.h"

TEST_CASE("Rate: Consistency")
{

  SECTION("No Spikes, rate is zero")
  {
    std::vector<double> spike_times= {};
    double rate = firing_rate(1, spike_times, 0.01);
    REQUIRE( rate == 0);
  };

};
