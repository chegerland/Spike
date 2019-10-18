#include <iostream>
#include <sys/stat.h>
#include <sstream>

// program options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

// filesystem
#include <boost/filesystem.hpp>
namespace filesys = boost::filesystem;

#include "Options.h"

Options::Options(int argc, char * argv[])
{
  /* Read command line options */
  try
  {
		// List all options and their description
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "Help screen")
    ("mode", po::value<int>(&(this->mode)), "Mode \n 0 = Simulation, 1 = Evaluation, 2 = Curves")
    ("file", po::value<std::string>(&(this->file)), "Input File");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

		// if the help option is given, show the flag description
    if (vm.count("help"))
    {
      std::cout << desc << std::endl;
      exit(0);
    };

  }
  catch(std::exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
  }

  /* check the given options */
  this->check();

};


// check the command line options
void Options::check()
{
		// check if file extension is right
    if ( mode == 0 )
    {
			// input file should be .json
      if ( getFileExtension(file) != ".json" )
      {
        std::cerr << "Input file must have extension .json!" << std::endl;
        exit(0);
      }

			// check if output file already exists
			std::string output_file = file.substr(0,file.find_last_of('.'))+".out";
			if ( exists(output_file) )
			{
				char input;
				std::cout << "Output file \"" << output_file << "\" already exists!\n"
									<< "Overwrite file? [y/n]" << std::endl;
				std::cin >> input;

				if ( input == 'n' )
				{
					exit(0);
				};
			};

    }
    else if ( mode == 1 )
    {
      std::cout << "Evaluation mode.\n" << std::endl;
			// Evaluation mode needs .out
      if ( getFileExtension(file) != ".json" )
      {
        std::cerr << "Input file must have extension .json!" << std::endl;
        exit(0);
      };

			// check if output file exists
			std::string output_file = file.substr(0,file.find_last_of('.'))+".out";
			if ( !exists(output_file) )
			{
				std::cout << "Spike times file \"" << output_file << "\" does not exist!\n";
				exit(0);
			};
    }
    else if ( mode == 2 )
    {
      std::cout << "Pretty curves mode.\n" << std::endl;
			// curves mode needs .out
      if ( getFileExtension(file) != ".json" )
      {
        std::cerr << "Input file must have extension .json!" << std::endl;
        exit(0);
      };
    }
    else
    {
			// if mode != 0 or 1, show error
      std::cerr << "Unknown mode. Please choose 0 (simulation) or 1 (evaluation)." << std::endl;
      exit(0);
    };
};

// Get File extension from File path or File Name
std::string getFileExtension(std::string filePath)
{
	// Create a Path object from given string
	filesys::path pathObj(filePath);
	// Check if file name in the path object has extension
	if (pathObj.has_extension()) {
		// Fetch the extension from path object and return
		return pathObj.extension().string();
	}
	// In case of no extension return empty string
	return "";
};

// check if given file exists
bool exists (const std::string& path)
{
  struct stat buffer;
  return (stat (path.c_str(), &buffer) == 0);
};

// read in spike train
std::vector<std::vector<double> > file_to_vector(std::string name)
{
	// define vector of spike trains
	std::vector<std::vector<double> > result;

	// define file stream
	std::ifstream input (name);
	std::string lineData;

	// get lines from file
	while(getline(input, lineData))
	{
		double d;
		std::vector<double> row;
		std::stringstream lineStream(lineData);

		while (lineStream >> d)
		row.push_back(d);

		result.push_back(row);
	}

	return result;
};
