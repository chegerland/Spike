# TimeFrame
```cpp
class TimeFrame
{
private:
  double t_0;    // start time
  double t_end;  // end time
  double dt;     // time step
  int steps;     // number of time steps

public:

  // constructors
  TimeFrame(std::string input_file);
  TimeFrame(double t_0, double t_end, double dt);

  // getter functions
  double get_t_0();
  double get_t_end();
  double get_dt();
  int get_steps();

  // print function
  void print_parameters();
};
```
