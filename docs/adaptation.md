# Adaptation
```cpp
class Adaptation
{
public:

  // returns f(a,t) = da/dt
  virtual double adapt(double a, double t) =0;

  // reset rule for a(t)
  virtual void reset_rule(double a) =0;
};
```

## ExpAdaptation
```cpp
class ExpAdaptation : public Adaptation
{
private:

  double Delta; // size of kick
  double tau_a; // time scale

public:

  // constructors
  ExpAdaptation(double Delta, double tau_a);
  ExpAdaptation(std::string input_file);

  // adaptation f(a,t) = da/dt = - 1/tau_a * a
  double adapt(double a, double t);

  // reset rule for a(t): a -> a + Delta
  void reset_rule(double a);
};
```
