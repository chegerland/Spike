#ifndef ADAPTATION_H
#define ADAPTATION_H

// Adaptation
class Adaptation
{
public:
  virtual double adapt(double a, double t) =0;
  virtual void reset_rule(double a) =0;
};


#endif // ADAPTATION_H
