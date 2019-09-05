# make library
add_library(inputoutput SHARED
  options.cpp
  filetools.cpp
)

set_target_properties(inputoutput PROPERTIES PUBLIC_HEADER include/inputoutput.h)
target_include_directories(inputoutput PRIVATE src/InputOutput)
