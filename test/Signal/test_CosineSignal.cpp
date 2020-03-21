#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("Cosine Signal constructors and calculation work", "[CosineSignal]") {
  SECTION("Constructor from .ini file") {
    CosineSignal sig("../data/test_files/CosineSignal_test.json");

    double t = 0.3;
    REQUIRE(sig.signal(t) == 3.0 * cos(2.0 * M_PI * 2.35 * t));
  };

  SECTION("Direct construction") {
    auto alpha = GENERATE(take(3, random(0.0, 1e2)));
    auto f = GENERATE(take(3, random(0.0, 1e2)));
    double t = 0.3;

    CosineSignal sig(alpha, f);

    REQUIRE(sig.signal(t) == alpha * cos(2.0 * M_PI * f * t));
  };
};
