#include <getopt.h>
#include <iostream>
#include <sys/stat.h>
#include <stdexcept>

#include "input_output.h"

// display usage 
void display_usage() {
  std::cout << "Spike" << "[options]" << std::endl <<
      "Options:" << std::endl <<
      "-h | --help        Print this help" << std::endl <<
      "-t | --test        Enable test mode" << std::endl <<
      "-f | --file        Set input file" << std::endl;
};

// commandline options and flags
void options(Files *files, int argc, char *argv[])
{
    // input routine copied from gnu getopt_long example
    int c;

    while (1) {
      static struct option long_options[] = 
      {
        {"file", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {"test", no_argument, 0, 't'},
        {0, 0, 0, 0}
      };

      int option_index = 0;

      c = getopt_long(argc, argv, "f:t:h", long_options, &option_index);

      if (c == -1) {
        break;
      }

      switch(c) {

       case 0:
         if (long_options[option_index].flag != 0)
           break;
         printf ("option %s", long_options[option_index].name);
         if (optarg)
           printf (" with arg %s", optarg);
         printf ("\n");
         break;

        case 'f':
          check_set_file(files, optarg);
          break;

        case 't':
          std::cout << "Test mode enabled!" << std::endl;
          break;

        case 'h':
        case '?':
          display_usage();
          break;

        default:
          break;
      }
    }
    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
      std::cout << "non-option ARGV-elements: ";
      while (optind < argc)
        std::cout << argv[optind++] << " ";

      std::cout << "\n" << std::endl;
    }
}

// replaces extension of file
void replace_extension(std::string& s, const std::string& newExt) 
{
  std::string::size_type i = s.rfind('.', s.length());

  if (i != std::string::npos) {
    s.replace(i+1, newExt.length(), newExt);
  }
};

// check input file and get name for output file
void check_set_file(Files *files, char optarg[])
{
  std::string output_file = optarg;
  replace_extension(output_file, "out");

  if (exists(optarg)) {
    throw std::logic_error("Input file already exists!");
    exit(0);
  } else if (exists(output_file)) {
    throw std::logic_error("Output file already exists!");
    exit(0);
  } else {
  files->input_file = optarg;
  files->output_file = output_file;
  }
}

// check if file exists
bool exists(const std::string& name) 
{
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}
