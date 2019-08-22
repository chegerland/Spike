#include "catch.hpp"
#include <math.h>

#include "models.h"
#include "simulation.h"

TEST_CASE("Perfect integrate and fire neuron")
{
  PIF *pif_neuron;
  pif_neuron = new PIF(3.4, 1.0);

  SECTION("Drift does not depend on v or t")
  {
    REQUIRE( pif_neuron->drift(2,4) == 3.4);
    REQUIRE( pif_neuron->drift(3,1) == 3.4);
  };

  SECTION("Diffusion does not depend on v or t")
  {
    REQUIRE( pif_neuron->diffusion(3,1) == sqrt(2));
    REQUIRE( pif_neuron->diffusion(2.4,5.5) == sqrt(2));
  };


  SECTION("Reproduce deterministic limit")
  {

    Simulation *sim;
    sim = new Simulation(0.0, 10.1, 1e-2);

    pif_neuron->set_if_params(1.0, 0.0);

    std::vector<double> spikes;
    pif_neuron->spike_times(spikes, sim);

    double rate = pif_neuron->rate_analytic();
    int spike_count = (int) rate*(sim->t_end - sim->t_0);

    REQUIRE( spikes.size() == spike_count );
  };
};


TEST_CASE("Leaky integrate and fire neuron")
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
