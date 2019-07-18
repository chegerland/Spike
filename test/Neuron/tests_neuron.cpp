#include "catch.hpp"
#include "../../src/Neuron/neuron.h"
#include <math.h>

TEST_CASE("Perfect integrate and fire neuron") {
  IF pif_neuron;


  SECTION("Drift does not depend on v or t") {
    pif_neuron.mu = 3.4;
    REQUIRE( pif_neuron.drift(2,4) == pif_neuron.mu);
    REQUIRE( pif_neuron.drift(3,1) == pif_neuron.mu);
  };

  SECTION("Diffusion does not depend on v or t") {
    pif_neuron.D = 1;
    REQUIRE( pif_neuron.diffusion(3,1) == sqrt(2));
    REQUIRE( pif_neuron.diffusion(2.4,5.5) == sqrt(2));
  };

  SECTION("Reproduce deterministic limit") {
    pif_neuron.t_0 = 0;
    pif_neuron.t_end = 10.1;
    pif_neuron.dt = 0.01;

    pif_neuron.D = 0;
    pif_neuron.mu = 1;

    std::vector<double> spikes;
    pif_neuron.spike_times(spikes);

    double rate = pif_neuron.rate_analytic();
    int spike_count = (int) rate*(pif_neuron.t_end - pif_neuron.t_0);

    REQUIRE( spikes.size() == spike_count );
  };
};


TEST_CASE("Leaky integrate and fire neuron") {
  LIF pif_neuron;


  SECTION("Drift does not depend t, but depends on v") {
    pif_neuron.mu = 3.4;
    REQUIRE( pif_neuron.drift(2,4) == pif_neuron.mu-2);
    REQUIRE( pif_neuron.drift(2,0.01) == pif_neuron.mu-2);
    REQUIRE( pif_neuron.drift(3.2,1) == pif_neuron.mu-3.2);
    REQUIRE( pif_neuron.drift(3.2,10.4) == pif_neuron.mu-3.2);
  };


  SECTION("Reproduce deterministic limit (weak noise, mean driven regime)") {
    pif_neuron.t_0 = 0;
    pif_neuron.t_end = 10.1;
    pif_neuron.dt = 1e-6;

    pif_neuron.D = 0;
    pif_neuron.mu = 150;

    std::vector<double> spikes;
    pif_neuron.spike_times(spikes);

    double rate = 1.0/log(pif_neuron.mu/(pif_neuron.mu-1.0));
    int spike_count = (int) (rate*(pif_neuron.t_end - pif_neuron.t_0));

    REQUIRE( spikes.size() == spike_count ); // decreasing dt does not change this result
  };

};
