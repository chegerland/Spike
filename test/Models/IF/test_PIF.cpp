#include "catch.hpp"
#include <math.h>

#include "models.h"

TEST_CASE("PIF: Drift")
{
  PIF *pif_neuron;
  pif_neuron = new PIF(3.4, 1.0);

  SECTION("Drift does not depend on v or t")
  {
    REQUIRE( pif_neuron->drift(2,4) == 3.4);
    REQUIRE( pif_neuron->drift(3,1) == 3.4);
  };
};

TEST_CASE("PIF: Diffusion")
{
  PIF *pif_neuron;
  pif_neuron = new PIF(3.4, 2.0);

  SECTION("Diffusion does not depend on v or t")
  {
    REQUIRE( pif_neuron->diffusion(2,4) == 2.0);
    REQUIRE( pif_neuron->diffusion(3,1) == 2.0);
  };
};

TEST_CASE("PIF: Analytic limits")
{
  SECTION("Reproduce deterministic limit")
  {
    // define neuron with no drift --> deterministic limit
    PIF *pif_neuron;
    pif_neuron = new PIF(1.0, 0.0);

    // define simulation
    Simulation *sim;
    sim = new Simulation(0.0, 10.1, 1e-2);

    std::vector<double> spikes;
    pif_neuron->spike_times(spikes, sim);

    double rate = pif_neuron->rate_analytic();
    int spike_count = (int) rate*(sim->t_end - sim->t_0);

    REQUIRE( spikes.size() == spike_count );
  };
};
