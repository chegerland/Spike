#include "LIF.h"

// constructors
LIF::LIF(double mu, double D) : IF(mu, D) { type = "LIF"; };
LIF::LIF(std::string input_file) : IF(input_file) { type = "LIF"; };

// drift of an LIF neuron
double LIF::drift(double v, double t) const { return (this->mu - v); };
