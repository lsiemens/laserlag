# minkowski Library

cmake_minimum_required(VERSION 3.10)

project(minkowski)

set(CMAKE_CXX_STANDARD 11)

find_package(glm REQUIRED)

add_library(minkowski STATIC
    src/point.cpp
    src/vector.cpp
    src/world_line.cpp)
target_include_directories(minkowski PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${GLM_INCLUDE_DIRS})
target_compile_options(minkowski PRIVATE -Wall -Wextra -Wpedantic)

# setup tests
enable_testing()
add_subdirectory(tests)
