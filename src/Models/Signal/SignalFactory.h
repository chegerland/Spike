#ifndef SIGNALFACTORY_H
#define SIGNALFACTORY_H

#include <string>
#include "Signal.h"

//! A signal factory
/*!
* Class that implements the factory design pattern for signals.
*/
class SignalFactory
{
public:
  static Signal *create(std::string input_file);
  
};

#endif // SIGNALFACTORY_H
