#include "../../extern/catch/catch.hpp"
#include "Spike.h"

TEST_CASE("SpikeTrain is constructed correctly"){
  unsigned int length = 10;
  SpikeTrain spike_train(length);

  // length is correct
  REQUIRE(spike_train.get_length() == length);

  // all entries are false
  for (unsigned int i = 0; i < length; i++) {
    REQUIRE(!spike_train.get_spike(i));
  }
}

TEST_CASE("Setting Spikes works as expected") {
  unsigned int length = 10;
  SpikeTrain spike_train(length);
  spike_train.set_spike(3);

  REQUIRE(spike_train.get_spike(3));
}
