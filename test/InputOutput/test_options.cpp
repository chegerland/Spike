#include "catch.hpp"

#include "inputoutput.h"

TEST_CASE("Options: get options")
{
  // simulate starting the program with some options
  int argc = 7;
  char *argv[argc];
  argv[0] = (char *)"./../bin/Spike";
  argv[1] = (char *)"--mode";
  argv[2] = (char *)"3";
  argv[3] = (char *)"--file";
  argv[4] = (char *)"test.out";
  argv[5] = (char *)"--rate";
  argv[6] = (char *)"1e-2";

  // get options struct from "command line options"
  Options *opts;
  opts = new Options();
  get_options(argc, argv, opts);

  // check if we got the mode right
  SECTION("Get mode")
  {
    REQUIRE(opts->mode == 3);
  };

  // check if we got the input file right
  SECTION("Get input file")
  {
    REQUIRE(opts->parameters == "test.out");
  };

  // check if we got the rate right
  SECTION("Get firing rate")
  {
    REQUIRE(opts->rate == true);
    REQUIRE(opts->dt == 1e-2);
  };

  // check if we got the isi right
  SECTION("Get isi")
  {
    REQUIRE(opts->isi == false);
  };
}
