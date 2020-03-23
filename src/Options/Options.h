#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

/**
 * @class Options
 * @brief Implements a class that handles command line options.
 */
class Options {
private:
  std::string input_file;  ///< path to input file
  std::string output_file; ///< path to output file

public:

  /**
   * @brief Construct Options from input file
   * @param input_file Input file in .json format
   */
  explicit Options(std::string input_file);

  /**
   * @brief Construct Options from command line arguments.
   * @param argc Number of arguments
   * @param argv Array containing command line arguments.
   */
  Options(int argc, char *argv[]);

  /**
   * Checks whether input file has right format (JSON) and whether output file
   * already exists.
   * @brief Checks the given input file.
   */
  void check();

  /**
   * @brief Getter method for input file
   * @return Input file
   */
  std::string get_input_file() { return this->input_file; };

  /**
   * @brief Getter method for output file.
   * @return Output file
   */
  std::string get_output_file() { return this->output_file; };
};

/**
 * @brief Returns the extension of a given file.
 * @param filePath Path to file
 * @return The extension, e.g. ".json".
 */
std::string getFileExtension(std::string filePath);

/**
 * @brief Checks whether file exists
 * @param path Path to file
 * @return True if file exists, false otherwise
 */
bool exists(const std::string &path);

#endif // OPTIONS_H
