#include <iostream>

// json parser
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

#include "IF/PIF.h"
#include "IF/LIF.h"
#include "IFadapt/PIFadapt.h"
#include "IFadapt/LIFadapt.h"

#include "NeuronFactory.h"

// creates a neuron depending on type given in .json file
Neuron *NeuronFactory::create(std::string input_file)
{
  // set return pointer to NULL
  Neuron *neuron = NULL;

  // Create a root
  pt::ptree root;

  // Load the json file in this ptree
  pt::read_json(input_file, root);

  // read simulation data into simulation variables
  std::string type = root.get<std::string>("Neuron.type");

  // set the appropriate return type
  if (type == "PIF")
  {
    neuron = new PIF(input_file);
  }
  else if (type == "LIF")
  {
    neuron = new LIF(input_file);
  }
  else if (type == "PIFadapt")
  {
    neuron = new PIFadapt(input_file);
  }
  else if (type == "LIFadapt")
  {
    neuron = new LIFadapt(input_file);
  }
  else
  {
    std::cerr << "Error: Unknown Neuron type (" << type << ")!\n" << std::endl;
    exit(0);
  };
  
  return neuron;
};
