#include "Susceptibility.h"

Susceptibility::Susceptibility(const std::shared_ptr<WhiteNoiseSignal> &signal)
    : signal(signal), count(0) {}

void Susceptibility::add_susceptibility(
    const std::vector<std::complex<double>> &suscept) {
  for (size_t i = 0; i < suscept_values.size(); i++) {
    suscept_values[i] = 1. / ((double)count + 1) *
                        ((double)count * suscept_values[i] + suscept[i]);
  }
  count++;
}
