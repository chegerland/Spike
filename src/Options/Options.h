#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

// Class for command line options
class Options
{
private:

  std::string file; // path to parameter file

public:

  // constructor
  Options(std::string file): file(file) {};
  Options(int argc, char * argv[]);

  // check input options
  void check();

  // getter function
  std::string get_file(){return this->file;};

};

// get extension of a file
std::string getFileExtension(std::string filePath);

// check if file exists
bool exists (const std::string& path);

#endif // OPTIONS_H
