#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

// Class for command line options
class Options
{
public:

  std::string file; // path to parameter file

  // constructor
  Options(int argc, char * argv[]);

  // check input options
  void check();

};

// get extension of a file
std::string getFileExtension(std::string filePath);

// check if file exists
bool exists (const std::string& path);

#endif // OPTIONS_H
