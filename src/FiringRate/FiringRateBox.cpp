#include "FiringRateBox.h"

void FiringRateBox::calculate() {
  for (int i = 0; i < time_frame.get_steps(); i++) {
    values[i] =
        1. / ((double)N_Neurons * time_frame.get_dt()) * spike_histogram[i];
  }
}