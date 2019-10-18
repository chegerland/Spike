#include "catch.hpp"
#include <math.h>

#include "models.h"

TEST_CASE("PIFadapt: Drift")
{
  PIFadapt *pifadapt_neuron;
  pifadapt_neuron = new PIFadapt("../data/test_files/pifadapt.json");

  SECTION("Drift does not depend on v or t")
  {
    REQUIRE( pifadapt_neuron->drift(2,4) == 3.0);
    REQUIRE( pifadapt_neuron->drift(3,1) == 3.0);
  };
};

TEST_CASE("PIFadapt: Diffusion")
{
  PIFadapt *pifadapt_neuron;
  pifadapt_neuron = new PIFadapt("../data/test_files/pifadapt.json");

  SECTION("Diffusion does not depend on v or t")
  {
    REQUIRE( pifadapt_neuron->diffusion(2,4) == 2.0);
    REQUIRE( pifadapt_neuron->diffusion(3,1) == 2.0);
  };
};
