#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("Exponential adaptation constructors work", "[ExpAdaptation]") {
  SECTION(".ini file constructor") {
    ExpAdaptation adapt("../data/test_files/ExpAdaptation_test.json");

    // check if Delta was read right
    REQUIRE(adapt.reset_rule(0) == 3.0);

    // check if tau_a was read right
    REQUIRE(adapt.adapt(1.0, 0.0) == -0.5);
  };

  SECTION("normal constructor") {
    auto Delta = GENERATE(take(3, random(0.0, 10.0)));
    auto tau_a = GENERATE(take(3, random(0.001, 10.0)));
    ExpAdaptation adapt(Delta, tau_a);

    // check if Delta was read right
    REQUIRE(adapt.reset_rule(0) == Delta);

    // check if tau_a was read right
    REQUIRE(adapt.adapt(1.0, 0.0) == -1.0 / tau_a);
  };
};

TEST_CASE("Exponential adaptation is calculated correctly", "[ExpAdaptation]") {
  auto tau_a = GENERATE(take(3, random(0.001, 10.0)));
  ExpAdaptation adapt(2.0, tau_a);

  // value is correct and independent of t
  auto a = GENERATE(take(3, random(-10.0, 10.0)));
  REQUIRE(adapt.adapt(a, 0.0) == -1.0 / tau_a * a);
  REQUIRE(adapt.adapt(a, 2.0) == -1.0 / tau_a * a);
  REQUIRE(adapt.adapt(a, 1e3) == -1.0 / tau_a * a);
};

TEST_CASE("Exponential adaptation reset rule is calculated correctly", "[ExpAdaptation]") {
  auto Delta = GENERATE(take(3, random(0.0, 10.0)));
  ExpAdaptation adapt(Delta, 0.1);

  // value is correct
  auto a = GENERATE(take(3, random(-10.0, 10.0)));
  REQUIRE(adapt.reset_rule(a) == a + Delta);
};
