#include "PIF.h"

// constructors
PIF::PIF(double mu, double D) : IF(mu, D) { this->type = "PIF"; };
PIF::PIF(std::string input_file) : IF(input_file) {
  assert(this->type == "PIF");
};

// drift of a PIF neuron
double PIF::drift(double v, double t) const { return this->mu; };
