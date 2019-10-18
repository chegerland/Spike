#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

//! Class for command line options
/*!
* Defines a struct to store the command line options.
*/
class Options
{
public:
  /*! Mode (0 = Simulation, 1 = Evaluation, others = unknown) */
  int mode;

  /*! path to input file containing parameters */
  std::string file;

  /*!
  * Reads options from the command line and stores them in an Options struct.
  * @param argc Number of arguments.
  * @param argv Character array containing command line options.
  */
  Options(int argc, char * argv[]);

  /*!
  * Checks the given command line options for consistency.
  */
  void check();

};

#endif // OPTIONS_H
