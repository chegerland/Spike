/**
 * @file IO.h
 * @author C. H. Egerland
 */
#ifndef SPIKE_IO_H
#define SPIKE_IO_H

#include <iostream>
#include <string>

namespace Spike {

/**
 * @brief Implements an input-output interface. Reads the command line for an
 * input file and defines according output file.
 */
class IO {
   private:
    std::string input_file;   ///< path to input file
    std::string output_file;  ///< path to output file
    std::string ending;       ///< ending of output file
    void (*help)();           ///< pointer to a help function

   public:
    /**
     * @brief Construct a new IO object.
     *
     * @param help pointer to help function
     * @param ending output file ending
     */
    IO(void (*help)(), const std::string &ending)
        : ending(ending), help(help){};

    /**
     * @brief Parses command line arguments.
     *
     * @param argc
     * @param argv
     */
    void parse_args(int argc, char *argv[]);

    /**
     * @brief Get the path to input file.
     *
     * @return path to input file
     */
    const std::string &get_input_file() const { return input_file; };

    /**
     * @brief Get the path to output file.
     *
     * @return path to output file
     */
    const std::string &get_output_file() const { return output_file; };
};

}  // namespace Spike

#endif  // SPIKE_IO_H