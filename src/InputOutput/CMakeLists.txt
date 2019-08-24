# make library
add_library(inputoutput SHARED
  inputoutput.cpp
)

set_target_properties(inputoutput PROPERTIES PUBLIC_HEADER include/inputoutput.h)
target_include_directories(inputoutput PRIVATE src/inputoutput)
