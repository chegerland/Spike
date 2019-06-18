#include <iostream>
#include <fstream>
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
