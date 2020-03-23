#ifndef SPIKETRAIN_H
#define SPIKETRAIN_H

class SpikeTrain {
private:
  unsigned int length; ///< length of the spike train
  bool *spikes;        ///< bool array containing the spikes

public:
  explicit SpikeTrain(unsigned int length);
  ~SpikeTrain();

  int spike_count();
  void clear();

  // set spike
  void set_spike(unsigned int i);

  // getter functions
  unsigned int get_length() const { return length; };
  bool get_spike(unsigned int i) const { return spikes[i]; };
};

#endif // SPIKETRAIN_H
