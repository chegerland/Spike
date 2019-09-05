#include "catch.hpp"
#include <math.h>

#include "models.h"

TEST_CASE("LIF: Drift")
{
  LIF *lif_neuron;
  lif_neuron = new LIF(3.4, 1.0);

  SECTION("Drift does not depend t, but depends on v")
  {
    REQUIRE( lif_neuron->drift(2,4) == 3.4-2);
    REQUIRE( lif_neuron->drift(2,0.01) == 3.4-2);
    REQUIRE( lif_neuron->drift(3.2,1) == 3.4-3.2);
    REQUIRE( lif_neuron->drift(3.2,10.4) == 3.4-3.2);
  };
};


TEST_CASE("LIF: Diffusion")
{
  LIF *lif_neuron;
  lif_neuron = new LIF(3.4, 2.0);

  SECTION("Diffusion does not depend t, but depends on v")
  {
    REQUIRE( lif_neuron->diffusion(2,4) == 2.0);
    REQUIRE( lif_neuron->diffusion(3.2,1) == 2.0);
    REQUIRE( lif_neuron->diffusion(3.2,10.4) == 2.0);
  };
};
