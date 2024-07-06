# minkowski Library

cmake_minimum_required(VERSION 3.10)

project(minkowski)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(minkowski STATIC
    src/point.cpp
    src/vector.cpp
    src/worldline.cpp)

# setup tests
enable_testing()
add_subdirectory(tests)
