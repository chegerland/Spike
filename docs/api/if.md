# IF

```cpp
class IF
{
protected:

  double mu;        // mobility
  double D;         // diffusion coefficient
  std::string type; // type of the IF

public:

  // constructors
  IF(double mu, double D);
  IF(std::string input_file);

  // drift and diffusion of IF neuron
  virtual double drift(double v, double t) const =0;
  double diffusion(double v, double t) const;

  // count spikes that occured in timeframe
  int count(TimeFrame *time) const;
  int count(TimeFrame *time, Signal *get_value) const;
  int count(TimeFrame *time, Adaptation *adapt) const;
  int count(TimeFrame *time, Signal *get_value, Adaptation *adapt) const;

  // calculate firing rate
  void firing_rate(std::vector<double> &rate, TimeFrame *time) const;
  void firing_rate(std::vector<double> &rate, TimeFrame *time, Signal *get_value) const;
  void firing_rate(std::vector<double> &rate, TimeFrame *time, Adaptation *adapt) const;
  void firing_rate(std::vector<double> &rate, TimeFrame *time, Signal *get_value, Adaptation *adapt) const;

  // get voltage curve, i.e. v(t) or v(t) and a(t)
  void voltage_curve(std::vector<double> &v, TimeFrame *time) const;
  void voltage_curve(std::vector<double> &v, std::vector<double> &a, TimeFrame *time, Adaptation *adapt) const;

  // print the parameters of this neuron
  void print_parameters() const;
};
```

## PIF
```cpp
class PIF : public IF
{
public:

  // constructors
  PIF(double mu, double D);
  PIF(std::string input_file);

  double drift(double v, double t) const;
};
```

## LIF
```cpp
class LIF : public IF
{
public:

  // constructors
  LIF(double mu, double D);
  LIF(std::string input_file);

  double drift(double v, double t) const;
};
```
