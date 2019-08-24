#include <iostream>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

// program options
#include <boost/program_options.hpp>
namespace po = boost::program_options;

// filesystem
#include <boost/filesystem.hpp>
namespace filesys = boost::filesystem;

#include "inputoutput.h"

void read_json()
{
  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json("../data/test.json", root);

  // read simulation data
  double test = root.get<double>("test");
  std::cout << test << std::endl;

  if ( root.find("Simulation.N") == root.not_found() )
  {
    std::cerr << "N not found" << std::endl;
  };
  int N = root.get<int>("Simulation.N", 0);
  std::cout << N << std::endl;
  double dt = root.get<double>("Simulation.dt", 0);
  std::cout << dt << std::endl;
};

void get_options(int argc, char * argv[])
{
  try
  {
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "Help screen")
    ("mode", po::value<int>(&mode), "Mode \n 0 = Simulation, 1 = Evaluation")
    ("file", po::value<std::string>(&input_file), "Input File");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
      std::cout << desc << std::endl;
    };
  }
  catch(std::exception& e)
  {
    std::cerr << "error: " << e.what() << std::endl;
  }
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
}

void check_options(int mode, std::string input_file)
{
    if ( mode == 0 )
    {
      std::cout << "Simulation mode." << std::endl;
      if ( getFileExtension(input_file) != ".json" )
      {
        std::cerr << "Input file in simulation mode should have extension .json!" << std::endl;
        exit(0);
      }
    }
    else if ( mode == 1 )
    {
      std::cout << "Evaluation mode." << std::endl;
      if ( getFileExtension(input_file) != ".out" )
      {
        std::cerr << "Input file in evaluation mode should have extension .out!" << std::endl;
        exit(0);
      }
    }
    else
    {
      std::cerr << "Unknown mode. Please choose 0 (simulation) or 1 (evaluation)." << std::endl;
      exit(0);
    };
};
