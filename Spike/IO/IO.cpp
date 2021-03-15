#include <iostream>

// program options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "Spike/IO/IO.h"

namespace Spike {

void IO::parse_args(int argc, char *argv[]) {
    try {
        // List all options and their description
        po::options_description desc("Allowed options");
        desc.add_options()("help,h", "Show the help screen")(
            "file,f", po::value<std::string>(&(input_file)),
            "Path to input file (.ini format)");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        // if the help option is given, show the flag description
        if (vm.count("help")) {
            help();
            std::cout << desc << std::endl;
            exit(0);
        }

        if (vm.count("file")) {
            /* set according output file */
            output_file =
                input_file.substr(0, input_file.find_last_of('.')) + ending;
        } else {
            std::cerr << "No input file given!\n";
            std::cout << desc << std::endl;
            exit(-1);
        }

    } catch (std::exception &e) {
        std::cerr << "error: " << e.what() << std::endl;
    }
}

} //namespace Spike