cmake_minimum_required(VERSION 3.13.4)

project("Spike" VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Ofast")

# set output
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# code coverage
if(CMAKE_COMPILER_IS_GNUCXX)
  LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules")
  include(CodeCoverage)
  APPEND_COVERAGE_COMPILER_FLAGS()
  set(COVERAGE_LCOV_EXCLUDES '${CMAKE_CURRENT_SOURCE_DIR}/lib/*' '/usr/include/**')
  SETUP_TARGET_FOR_COVERAGE_LCOV(NAME Spike_coverage
    EXECUTABLE test_Spike
    )
endif()

# directories
add_subdirectory("src")
add_subdirectory("lib")
add_subdirectory("test")
