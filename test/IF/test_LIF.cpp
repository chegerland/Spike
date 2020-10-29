#include "extern/catch/catch.hpp"
#include "Spike/Spike.h"

using namespace Spike;

TEST_CASE("LIF Constructors, Drift and Diffusion work", "[LIF]") {
  SECTION(".ini file constructor") {
    LIF lif("../data/test_files/LIF_test.ini");

    // check mu
    REQUIRE(lif.drift(0.0) == 1.14);

    // check D
    REQUIRE(lif.diffusion() == 2.0);
  }

  SECTION("normal constructor") {
    auto mu = GENERATE(take(3, random(0.0, 1e2)));
    auto D = GENERATE(take(3, random(0.0, 10.0)));

    LIF lif(mu, D);

    REQUIRE(lif.drift(0.0) == mu);
    REQUIRE(lif.diffusion() == sqrt(2.0 * D));
  }
}
