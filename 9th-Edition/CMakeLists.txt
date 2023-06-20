# CMakeList.txt : CMake project for WH40k Randomizer, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("WH40k Randomizer")

# Add source to this project's executable.
add_executable (CMakeTarget "WH40k Randomizer.cpp" "WH40k Randomizer.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
