#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("SpikeTrain is constructed correctly"){
  TimeFrame time_frame(0.0, 10.0, 1e-2);
  SpikeTrain spike_train(time_frame);

  // length is correct
  REQUIRE(spike_train.get_size() == time_frame.get_size());

  // all entries are false
  for (size_t i = 0; i < spike_train.get_size(); i++) {
    REQUIRE(!spike_train.get_spike(i));
  }
}

TEST_CASE("Setting Spikes works as expected") {
  TimeFrame time_frame(0.0, 10.0, 1e-2);
  SpikeTrain spike_train(time_frame);
  spike_train.add_spike(3);

  REQUIRE(spike_train.get_spike(3));
}
