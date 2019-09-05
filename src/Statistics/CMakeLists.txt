# make library
add_library(statistics SHARED
  rate.cpp
  isi.cpp
)

set_target_properties(statistics PROPERTIES PUBLIC_HEADER include/statistics.h)
target_include_directories(statistics PRIVATE src/Statistics)
