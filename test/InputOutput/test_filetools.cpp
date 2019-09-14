#include "catch.hpp"

#include <string>
#include "inputoutput.h"

TEST_CASE("File Tools")
{
  SECTION("Get file extension")
  {
    std::string file = "../src/spike.cpp";
    std::string extension = getFileExtension(file);
    REQUIRE(extension == ".cpp");
  };

  SECTION("Check file existance")
  {
    std::string file = "../src/spike.cpp";
    REQUIRE(exists(file) == true);
  };
};
