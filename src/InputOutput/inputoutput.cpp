#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/stat.h>

#include "inputoutput.h"

// Prints the contents of vectors x and y to standard output.
void write_to_stdout(const std::vector<double> &x, const std::vector<double> &y)
{
    // vectors have to be same size
    if (x.size() != y.size())
    {
        std::cout << "Output vectors do not have the same length!" << std::endl;
        exit(0);
    };

    // loop over entries
    for (int i = 0; i < x.size(); i++)
    {
        std::cout << x[i] << " " << y[i] << std::endl;
    };
};

// Prints the contents of vectors x and y to a file with fileName.
void write_to_file(char fileName[100], const std::vector<double> &x, const std::vector<double> &y)
{
    // vectors have to be same size
    if (x.size() != y.size())
    {
        std::cout << "Output vectors do not have the same length!" << std::endl;
        exit(0);
    };

    // open filestream
    std::ofstream file;
    file.open(fileName);

    // loop over entries
    for (int i = 0; i < x.size(); i++)
    {
        file << x[i] << "," << y[i] << "\n";
    };

    file.close(); // close file
};

// Replace extension
void replace_extension(std::string& s, const std::string& newExt) 
{
  std::string::size_type i = s.rfind('.', s.length());
  std::cout << i << std::endl;

  if (i != std::string::npos) {
    s.replace(i+1, newExt.length(), newExt);
  }
};

// check if file exists
bool exists_test(const std::string& name) 
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}
