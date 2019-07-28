#include "catch.hpp"
#include <math.h>

#include "../../src/IO/input_output.h"

TEST_CASE("Check set file") {

  Files files;

  SECTION("Output name is input name with replaced extension") {
    char name[] = "test.in";
    check_set_file(&files, name);
    REQUIRE(files.output_file == "test.out");
  };

  SECTION("Failure if output file exists") {
    char name[] = "../data/test.in";
    REQUIRE_THROWS_WITH( check_set_file(&files, name), "Output file already exists!");
  };

  SECTION("Failure if input file exists") {
    char name[] = "../src/spike.cpp";
    REQUIRE_THROWS_WITH( check_set_file(&files, name), "Input file already exists!");
  };

};
