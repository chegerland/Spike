#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("PIF Constructors, Drift and Diffusion work", "[PIF]") {
  SECTION(".ini file constructor") {
    PIF pif("../data/test_files/PIF_test.ini");

    // check mu
    REQUIRE(pif.drift(0.0) == 1.14);

    // check D
    REQUIRE(pif.diffusion() == 2.0);
  }

  SECTION("normal constructor") {
    auto mu = GENERATE(take(3, random(0.0, 1e2)));
    auto D = GENERATE(take(3, random(0.0, 10.0)));

    PIF pif(mu, D);

    REQUIRE(pif.drift(0.0) == mu);
    REQUIRE(pif.diffusion() == sqrt(2.0 * D));
  }
}
