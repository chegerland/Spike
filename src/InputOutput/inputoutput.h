#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <vector>

// output
void write_to_stdout(const std::vector<double> &x, const std::vector<double> &y);
void write_to_file(char fileName[100], const std::vector<double> &x, const std::vector<double> &y);

#endif // ifndef
