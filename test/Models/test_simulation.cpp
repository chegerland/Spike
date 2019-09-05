#include "catch.hpp"

#include "models.h"

TEST_CASE("Simulation: Constructors")
{
    SECTION("Constructor for single neuron")
    {
      Simulation *sim;
      sim = new Simulation(0, 8, 1e-3);

      REQUIRE(sim->t_0 == 0);
      REQUIRE(sim->t_end == 8);
      REQUIRE(sim->dt == 1e-3);
      REQUIRE(sim->N == 1);
    };


    SECTION("Full constructor")
    {
      Simulation *sim;
      sim = new Simulation(1, 9, 1e-2, 10);

      REQUIRE(sim->t_0 == 1);
      REQUIRE(sim->t_end == 9);
      REQUIRE(sim->dt == 1e-2);
      REQUIRE(sim->N == 10);
    };

    SECTION("Constructor from file")
    {
      Simulation *sim;
      sim = new Simulation("../data/test.json");

      REQUIRE(sim->t_0 == 1);
      REQUIRE(sim->t_end == 8);
      REQUIRE(sim->dt == 1e-3);
      REQUIRE(sim->N == 5);
    };
}
