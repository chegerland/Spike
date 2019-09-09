#include <sys/stat.h>
#include <sstream>

// filesystem
#include <boost/filesystem.hpp>
namespace filesys = boost::filesystem;

#include "filetools.h"

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
