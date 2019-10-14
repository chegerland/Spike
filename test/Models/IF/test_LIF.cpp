#include "catch.hpp"
#include <math.h>

#include "models.h"

TEST_CASE("LIF: Drift")
{
  LIF *lif_neuron;
  lif_neuron = new LIF("../data/test_files/lif.json");

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
  lif_neuron = new LIF("../data/test_files/lif.json");
  lif_neuron = new LIF(3.4, 2.0);

  SECTION("Diffusion does not depend t, but depends on v")
  {
    REQUIRE( lif_neuron->diffusion(2,4) == 2.0);
    REQUIRE( lif_neuron->diffusion(3.2,1) == 2.0);
    REQUIRE( lif_neuron->diffusion(3.2,10.4) == 2.0);
  };
};

TEST_CASE("LIF: Analytic limits")
{
  SECTION("Deterministic limit (D = 0)")
  {
    // define lif with no drift
    LIF *lif_neuron;
    lif_neuron = new LIF(2.0, 0.0);

    // define Simulation
    Simulation *sim;
    sim = new Simulation(0.0, 20.0, 1e-5);

    std::vector<double> spikes;
    lif_neuron->spike_times(spikes, sim);

    double rate = lif_neuron->rate_analytic();
    int spike_count = (int) (rate*(sim->t_end - sim->t_0));

    REQUIRE( spikes.size() == spike_count );

  };
};
