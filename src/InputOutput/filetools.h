#ifndef FILETOOLS_H
#define FILETOOLS_H

#include <string>
#include <vector>

/*!
* Gets the extension of a given file.
* @param file_path Path to the file.
*/
std::string getFileExtension(std::string filePath);

/*!
* Check if file exists
* @params path File path
*/
bool exists (const std::string& path);

/*!
* Read in a spike train ensemble from a file
* @params name File path
*/
std::vector<std::vector<double> > file_to_vector(std::string name);

#endif // FILETOOLS_H
