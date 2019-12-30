#ifndef TWOCOSINE_H
#define TWOCOSINE_H

#include <string>

#include "Signal.h"

class Cosine : public Signal
{
private:

  // amplitube
  double alpha;

  // frequency
  double f;

public:

  /*!
  * Constructs a two cosine signal from .json file
  * @param input_file .json file with parameters
  */
  Cosine(std::string input_file);

  /*!
  * Returns signal of the form \f$ s(t) = \varepsilon(\alpha \cos(2 \pi f_1 t) + \beta \cos(2 \pi f_2 t))\f$.
  * @param t time at which the signal shall be evaluated.
  */
  double signal(double t);

  /*!
  * Prints signal parameters
  */
  void print_parameters();

};

#endif //TWOCOSINE_H
