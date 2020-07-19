#ifndef SPIKETRAIN_H
#define SPIKETRAIN_H

#include <cstddef>
#include <memory>
#include <vector>

#include "../TimeFrame/TimeFrame.h"

class SpikeTrain {
private:
  double dt;
  std::vector<double> spikes;

public:
  explicit SpikeTrain(const TimeFrame &time_frame);

  int spike_count();
  void clear();
  void add_spike(size_t i);

  [[nodiscard]] double get_dt() const { return dt; };
  [[nodiscard]] size_t get_size() const { return spikes.size(); };
  [[nodiscard]] bool get_spike(size_t i) const { return (spikes[i] != 0); };
  [[nodiscard]] const std::vector<double> &get_values() const {
    return spikes;
  };
};

#endif // SPIKETRAIN_H
