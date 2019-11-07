cmake_minimum_required(VERSION 3.10)

project(sampleCmake)

# The version number.
set (Sample_VERSION_MAJOR 0)
set (Sample_VERSION_MINOR 0)
set (Sample_VERSION_PATCH 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/version.h.in"
  "${PROJECT_BINARY_DIR}/version.h"
  )

# add the binary tree to the search path for include files
include_directories("${PROJECT_BINARY_DIR}")

# add the executable
add_executable(MENU menu.cpp)

target_compile_features (MENU PUBLIC cxx_std_11)