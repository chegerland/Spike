#include "catch.hpp"
#include "../src/Models/models.h"

TEST_CASE("Trivial test") {
    REQUIRE(1 == 1);
};


TEST_CASE("Voltage Curve") {

    // define PIF neuron
    IF *P = new IF();
    P->t_0 = 0;
    P->t_end = 8;
    P->N = 1000;
    P->mu = 1;
    P->D = 0.02;
   

    std::vector<double> t;
    std::vector<double> v;

    voltage_curve(P, t, v);
 
    REQUIRE(t[0] == P->t_0);
    REQUIRE(v[0] == 0);
};
