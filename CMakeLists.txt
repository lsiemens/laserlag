# minkowski & poincare

cmake_minimum_required(VERSION 3.10)
project(minkowski_poincare)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

# add libraries
add_subdirectory(minkowski)
add_subdirectory(poincare)

# activate testing
enable_testing()
