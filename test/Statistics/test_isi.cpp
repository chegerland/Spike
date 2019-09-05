#include "catch.hpp"
#include <math.h>

#include "statistics.h"

TEST_CASE("Interspike Intervals")
{
  SECTION("N spike times means N-1 interspikes")
  {

    std::vector<double> spike_times= {1, 3, 7, 9.5, 12.44, 15.02};
    std::vector<double> isis = isi(spike_times);
    REQUIRE(isis.size() == spike_times.size() - 1);
  };

  SECTION("Correct calculation")
  {
    std::vector<double> spike_times= {1, 3, 7, 9.5};
    std::vector<double> isis = isi(spike_times);
    REQUIRE(isis[0] == 2);
    REQUIRE(isis[1] == 4);
    REQUIRE(isis[2] == 2.5);
  };
};
