#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("Two Cosine Signal constructors and calculation work",
          "[TwoCosineSignal]") {
  SECTION("Constructor from .ini file") {

    const std::string file = "../data/test_files/TwoCosineSignal_test.ini";
    const TimeFrame time_frame(file);
    TwoCosineSignal sig(file, time_frame);

    double t = 0.3;
    REQUIRE(sig.signal(t) == 3.0 * cos(2.0 * M_PI * 2.35 * t) +
                                 4.0 * cos(2.0 * M_PI * 2.15 * t + 1.0));
  }

  SECTION("Direct construction") {

    const TimeFrame time_frame(0.0, 10.0, 0.1);
    double t = 0.3;

    auto alpha = GENERATE(take(3, random(0.0, 1e2)));
    auto beta = GENERATE(take(3, random(0.0, 1e2)));
    auto f1 = GENERATE(take(3, random(0.0, 1e2)));
    auto f2 = GENERATE(take(3, random(0.0, 1e2)));
    auto phi = GENERATE(take(3, random(0.0, 1e2)));

    TwoCosineSignal sig(alpha, f1, beta, f2, phi, time_frame);

    REQUIRE(sig.signal(t) == alpha * cos(2.0 * M_PI * f1 * t) +
                                 beta * cos(2.0 * M_PI * f2 * t + phi));
  }
}
