#include "Spike.h"
#include "catch.hpp"
#include <iostream>

TEST_CASE("Options constructors work", "[Options]") {
  SECTION("direct construction") {
    std::string file = "../README.json";
    Options opts(file);
    REQUIRE(opts.get_input_file() == file);
  };

  SECTION("construction with command line arguments") {
    // simulate command line arguments
    int argc = 3;
    char *argv[argc];
    argv[0] = (char *)"./../bin/Spike";
    argv[1] = (char *)"--file";
    argv[2] = (char *)"../data/NonExistantFile.json";

    Options opts(argc, argv);

    REQUIRE(opts.get_input_file() == "../data/NonExistantFile.json");
    REQUIRE(opts.get_output_file() == "../data/NonExistantFile.csv");
  };
};
