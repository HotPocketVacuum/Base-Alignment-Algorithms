cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Set C++ standard to C++11 (or higher if needed)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find package
find_package(Catch2 REQUIRED)

# Add main program executable (not used in testing)
add_executable(nw nw.cpp)

# Add a library for main function (to be used in testing)
add_library(helpers helpers.cpp)

# Include the subdirectory for tests
add_subdirectory(tests)