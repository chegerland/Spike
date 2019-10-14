#include "catch.hpp"
#include <math.h>

#include "models.h"

TEST_CASE("LIFadapt: Drift")
{
  LIFadapt *lifadapt_neuron;
  lifadapt_neuron = new LIFadapt("../data/test_files/lifadapt.json");

  SECTION("Drift does not depend t, but depends on v")
  {
    REQUIRE( lifadapt_neuron->drift(2,4) == 3.4-2);
    REQUIRE( lifadapt_neuron->drift(2,0.01) == 3.4-2);
    REQUIRE( lifadapt_neuron->drift(3.2,1) == 3.4-3.2);
    REQUIRE( lifadapt_neuron->drift(3.2,10.4) == 3.4-3.2);
  };
};

TEST_CASE("LIFadapt: Diffusion")
{
  LIFadapt *lifadapt_neuron;
  lifadapt_neuron = new LIFadapt("../data/test_files/lifadapt.json");

  SECTION("Diffusion does not depend t, but depends on v")
  {
    REQUIRE( lifadapt_neuron->diffusion(2,4) == 2.0);
    REQUIRE( lifadapt_neuron->diffusion(3.2,1) == 2.0);
    REQUIRE( lifadapt_neuron->diffusion(3.2,10.4) == 2.0);
  };
};
