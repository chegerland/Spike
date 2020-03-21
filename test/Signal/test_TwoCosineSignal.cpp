#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("Two Cosine Signal constructors and calculation work",
          "[TwoCosineSignal]") {
  SECTION("Constructor from .ini file") {
    TwoCosineSignal sig("../data/test_files/TwoCosineSignal_test.json");

    double t = 0.3;
    REQUIRE(sig.signal(t) == 3.0 * cos(2.0 * M_PI * 2.35 * t) +
                                 4.0 * cos(2.0 * M_PI * 2.15 * t + 1.0));
  };

  SECTION("Direct construction") {
    auto alpha = GENERATE(take(3, random(0.0, 1e2)));
    auto beta = GENERATE(take(3, random(0.0, 1e2)));
    auto f1 = GENERATE(take(3, random(0.0, 1e2)));
    auto f2 = GENERATE(take(3, random(0.0, 1e2)));
    auto phi = GENERATE(take(3, random(0.0, 1e2)));
    double t = 0.3;

    TwoCosineSignal sig(alpha, f1, beta, f2, phi);

    REQUIRE(sig.signal(t) == alpha * cos(2.0 * M_PI * f1 * t) +
                                 beta * cos(2.0 * M_PI * f2 * t + phi));
  };
};
