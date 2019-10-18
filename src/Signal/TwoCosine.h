#ifndef TWOCOSINE_H
#define TWOCOSINE_H

#include <string>

#include "Signal.h"

class TwoCosine : public Signal
{
private:

  /*! overall signal strength */
  double eps;
  /*! amplitude first signal */
  double alpha;
  /*! amplitude second signal */
  double beta;
  /*! phase shift */
  double phi;
  /*! frequency first signal */
  double f1;
  /*! frequency second signal */
  double f2;

public:

  /*!
  * Constructs a two cosine signal from .json file
  * @param input_file .json file with parameters
  */
  TwoCosine(std::string input_file);

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
