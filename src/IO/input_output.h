#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <string>

struct Files
{
    std::string input_file;
    std::string output_file;
};

//! Display usage of the program
void display_usage();

//! Command line options.
/*!
 * Reads the command line options given in flag form (e.g. -f) and long form (e.g. --file) and defines the files accordingly.
 */
void options(Files *files, int argc, char *argv[]);


//! Check input file and set output file.
/*!
 * Changes the extension of the input file to define output file. Checks whether input or output file exists and if not defines the input and output file entry in the Files struct.
 */
void check_set_file(Files *files, char optarg[]);

//! Replaces extension of string s with newExt.
void replace_extension(std::string& s, const std::string& newExt);

//! Checks if file 'name' exists.
bool exists(const std::string& name);


#endif // INPUT_OUTPUT_H
