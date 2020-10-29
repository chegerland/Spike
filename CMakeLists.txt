cmake_minimum_required(VERSION 3.10)

# set c++ standard
set(CMAKE_CXX_STANDARD 17)

# set general compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -Wpedantic")

# CMake useful directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Project name and version
project("Spike")
set(VERSION 0.1)

# add the cmake path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/findFFTW/")

# find FFTW, gsl, mpi
find_package(FFTW REQUIRED)
find_package(GSL REQUIRED)
find_package(MPI REQUIRED)

# find boost package
set(Boost_NO_BOOST_CMAKE ON)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS unit_test_framework program_options filesystem system thread log REQUIRED)

# include directories
include_directories(${PROJECT_SOURCE_DIR})

# add catch2
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE ${PROJECT_SOURCE_DIR}/include)

# directories
add_subdirectory("Spike")
add_subdirectory("app")
add_subdirectory("test")
