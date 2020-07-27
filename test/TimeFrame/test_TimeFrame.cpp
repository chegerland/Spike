#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("TimeFrame is initialized correctly") {
  SECTION("with direct constructor") {
    double t_0 = 0.0;
    double t_end = 10.0;
    double dt = 0.1;
    TimeFrame time_frame(t_0, t_end, dt);

    // check parameters
    REQUIRE(time_frame.get_t_0() == t_0);
    REQUIRE(time_frame.get_t_end() == t_end);
    REQUIRE(time_frame.get_dt() == dt);
    REQUIRE(time_frame.get_size() == 101);

    // check if array is defined correctly
    REQUIRE(time_frame.get_time(3) == Approx(.3));
    REQUIRE(time_frame.get_time(100) == Approx(10));
  }

  SECTION("with .json constructor") {
    const std::string file = "../data/test_files/TimeFrame_test.ini";
    TimeFrame time_frame(file);

    // check parameters
    REQUIRE(time_frame.get_t_0() == 0.0);
    REQUIRE(time_frame.get_t_end() == 10.0);
    REQUIRE(time_frame.get_dt() == 0.1);
    REQUIRE(time_frame.get_size() == 101);

    // check if array is defined correctly
    REQUIRE(time_frame.get_time(3) == Approx(.3));
    REQUIRE(time_frame.get_time(100) == Approx(10));
  }
}
