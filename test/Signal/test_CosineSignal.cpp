#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("Cosine Signal constructors and calculation work", "[CosineSignal]") {
  SECTION("Constructor from .json file") {
    const std::string file = "../data/test_files/CosineSignal_test.json";
    const TimeFrame time_frame(file);
    CosineSignal sig(file, time_frame);

    double t = 0.3;
    REQUIRE(sig.signal(t) == 3.0 * cos(2.0 * M_PI * 2.35 * t));
  }

  SECTION("Direct construction") {
    const TimeFrame time_frame(0.0, 10.0, 0.1);
    double t = 0.3;

    auto alpha = GENERATE(take(3, random(0.0, 1e2)));
    auto f = GENERATE(take(3, random(0.0, 1e2)));

    CosineSignal sig(alpha, f, time_frame);

    REQUIRE(sig.signal(t) == alpha * cos(2.0 * M_PI * f * t));
    REQUIRE(sig.get_value(3) ==
            alpha * cos(2.0 * M_PI * f * time_frame.get_time(3)));
  }
}
