#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <string>

int mode;
std::string input_file;

void read_json();
void get_options(int argc, char * argv[]);
std::string getFileExtension(std::string filePath);
void check_options(int mode, std::string input_file);

#endif // INPUTOUTPUT_H
