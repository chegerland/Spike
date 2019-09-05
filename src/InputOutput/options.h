#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

//! Struct for command line options
/*!
* Defines a struct to store the command line options.
*/
struct Options {
  /*! Mode (0 = Simulation, 1 = Evaluation, others = unknown) */
  int mode;

  /*! path to input file containing parameters */
  std::string parameters;

  /*! firing rate flag and time bin */
  bool rate = false;
  double dt;

  /*! isi flag */
  bool isi = false;
};

/*!
* Reads options from the command line and stores them in an Options struct.
* @param argc Number of arguments.
* @param argv Character array containing command line options.
* @param options Options struct where the command line options will be stored.
*/
void get_options(int argc, char * argv[], Options *options);

/*!
* Checks the given command line options for consistency
* @param options Options struct containing the command line options.
*/
void check_options(Options *options);

#endif // OPTIONS_H
