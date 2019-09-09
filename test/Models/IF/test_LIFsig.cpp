#include "catch.hpp"
#include <math.h>

#include "models.h"

TEST_CASE("LIFsig: Drift")
{
  LIFsig *lifsig_neuron;
  lifsig_neuron = new LIFsig("../data/test/lifsig.json");

  SECTION("Drift depends on t and v")
  {
    REQUIRE( lifsig_neuron->drift(2.0,4.0) == 1.0133475635416487);
    REQUIRE( lifsig_neuron->drift(2.0,2.0) == 0.9835845750948746);
  };
};

TEST_CASE("LIFsig: Diffusion")
{
  LIFsig *lifsig_neuron;
  lifsig_neuron = new LIFsig("../data/test/lifsig.json");

  SECTION("Diffusion does not depend t, but depends on v")
  {
    REQUIRE( lifsig_neuron->diffusion(2,4) == 1.2649110640673518);
    REQUIRE( lifsig_neuron->diffusion(3.2,1) == 1.2649110640673518);
    REQUIRE( lifsig_neuron->diffusion(3.2,10.4) == 1.2649110640673518);
  };
};
