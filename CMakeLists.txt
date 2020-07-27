cmake_minimum_required(VERSION 3.10)

# set c++ standard
set(CMAKE_CXX_STANDARD 17)

# set general compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -lfftw3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -Wpedantic")

# CMake useful directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Project name and version
project("Spike")
set(VERSION 0.1)

# find boost package
set(Boost_NO_BOOST_CMAKE ON)
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package(Boost COMPONENTS unit_test_framework program_options filesystem system thread log REQUIRED)

# find openmp
find_package(OpenMP)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
find_package(MPI)

# include armadillo
find_package(LAPACK REQUIRED)
find_package(BLAS REQUIRED)
include_directories("${PROJECT_SOURCE_DIR}/extern/armadillo-9.860.1/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DARMA_DONT_USE_WRAPPER")


# include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_BINARY_DIR}/include
  ${Boost_INCLUDE_DIR}
)

# catch2
add_library(catch2 INTERFACE)
target_include_directories(catch2 INTERFACE ${PROJECT_SOURCE_DIR}/include)


# directories
add_subdirectory("src")
add_subdirectory("app")
add_subdirectory("test")
