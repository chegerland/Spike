# Signal
```cpp
class Signal
{
public:

  // Returns the signal at time t
  virtual double signal(double t) =0;

  // print signal parameters
  virtual void print_parameters() =0;
};
```

## CosineSignal
```cpp
class CosineSignal : public Signal
{
private:

  double alpha; // amplitube
  double f;     // frequency

public:

  // constructors
  CosineSignal(double alpha, double f);
  CosineSignal(std::string input_file);

  // return signal
  double signal(double t);

  // getter functions
  double get_alpha(){return this->alpha;};
  double get_f(){return this->f;};

  // print function
  void print_parameters();

};
```

## TwoCosineSignal
```cpp
class TwoCosineSignal : public Signal
{
private:

  double alpha; // amplitude first signal
  double beta;  // amplitude second signal
  double phi;   // phase shift
  double f1;    // frequency first signal
  double f2;    // frequency second signal

public:

  // constructors
  TwoCosineSignal(double alpha, double beta, double phi, double f1, double f2);
  TwoCosineSignal(std::string input_file);

  // return signal
  double signal(double t);

  // print function
  void print_parameters();

};
```
