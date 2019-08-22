#include "catch.hpp"
#include <math.h>

#include "../../src/Statistics/Statistics.h"

TEST_CASE("Firing rate")
{

  SECTION("No Spikes, rate is zero")
  {
    std::vector<double> spike_times= {};
    REQUIRE(firing_rate(1, spike_times, 0.01) == 0);
  };

};
