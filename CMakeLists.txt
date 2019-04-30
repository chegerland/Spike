cmake_minimum_required(VERSION 3.13.4)
project(spike VERSION 0.1
              DESCRIPTION "Numerical project for master thesis")

# include directory
include_directories(include)
include_directories(src)

# add sources
file(GLOB SOURCES "src/factorial.cpp")
file(GLOB TESTSOURCES "test/*.cpp")

add_executable(spike src/spike.cpp ${SOURCES})
add_executable(Test ${TESTSOURCES} ${SOURCES})

# TEST
include(CTest)
enable_testing()
add_test(NAME FirstTest
         COMMAND Test)
