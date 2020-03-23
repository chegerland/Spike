# Signal
```cpp
class Signal
{
public:

  // Returns the get_value at time t
  virtual double get_value(double t) =0;

  // print get_value parameters
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

  // return get_value
  double get_value(double t);

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

  double alpha; // amplitude first get_value
  double beta;  // amplitude second get_value
  double phi;   // phase shift
  double f1;    // frequency first get_value
  double f2;    // frequency second get_value

public:

  // constructors
  TwoCosineSignal(double alpha, double beta, double phi, double f1, double f2);
  TwoCosineSignal(std::string input_file);

  // return get_value
  double get_value(double t);

  // print function
  void print_parameters();

};
```
