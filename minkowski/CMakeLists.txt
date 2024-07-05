cmake_minimum_required(VERSION 3.10)

project(minkowski)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_library(minkowski STATIC
    src/point.cpp
    src/vector.cpp
    src/worldline.cpp)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_point tests/test_point.cpp)
target_link_libraries(test_point ${GTEST_LIBRARIES} pthread minkowski)

add_test(NAME test_point COMMAND test_point)
