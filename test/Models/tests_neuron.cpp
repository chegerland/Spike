#include "catch.hpp"
#include "models.h"
#include <math.h>

TEST_CASE("Perfect integrate and fire neuron") {
  PIF pif_neuron;

  double mu = 3.4;
  double D = 1;
  pif_neuron.set_if_params(mu, D);

  SECTION("Drift does not depend on v or t") {
    REQUIRE( pif_neuron.drift(2,4) == 3.4);
    REQUIRE( pif_neuron.drift(3,1) == 3.4);
  };

  SECTION("Diffusion does not depend on v or t") {
    REQUIRE( pif_neuron.diffusion(3,1) == sqrt(2));
    REQUIRE( pif_neuron.diffusion(2.4,5.5) == sqrt(2));
  };


  SECTION("Reproduce deterministic limit") {
    double t_0 = 0;
    double t_end = 10.1;
    double dt = 0.01;
    mu = 1;
    D = 0;

    pif_neuron.set_if_params(mu, D);
    pif_neuron.set_simulation_params(t_0, t_end, dt);

    std::vector<double> spikes;
    pif_neuron.spike_times(spikes);

    double rate = pif_neuron.rate_analytic();
    int spike_count = (int) rate*(t_end - t_0);

    REQUIRE( spikes.size() == spike_count );
  };
};


TEST_CASE("Leaky integrate and fire neuron") {
  LIF pif_neuron;

  double mu = 3.4;
  double D = 1;
  pif_neuron.set_if_params(mu, D);

  SECTION("Drift does not depend t, but depends on v") {
    REQUIRE( pif_neuron.drift(2,4) == 3.4-2);
    REQUIRE( pif_neuron.drift(2,0.01) == 3.4-2);
    REQUIRE( pif_neuron.drift(3.2,1) == 3.4-3.2);
    REQUIRE( pif_neuron.drift(3.2,10.4) == 3.4-3.2);
  };
};
