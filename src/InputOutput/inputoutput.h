#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

// output
void write_to_stdout(const std::vector<double> &x, const std::vector<double> &y);
void write_to_file(char fileName[100], const std::vector<double> &x, const std::vector<double> &y);


void replace_extension(std::string& s, const std::string& newExt);
bool exists_test(const std::string& name);

#endif // ifndef
