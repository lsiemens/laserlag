cmake_minimum_required(VERSION 3.10)

project(poincare)

set(CMAKE_CXX_STANDARD 11)

find_package(glfw3 3.3 REQUIRED)
include_directories(include)

add_library(poincare STATIC
    src/update_logger.cpp
    src/frame_timer.cpp)
target_link_libraries(poincare glfw)

# setup tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_update_logger tests/test_update_logger.cpp)
target_link_libraries(test_update_logger ${GTEST_LIBRARIES} pthread poincare)

add_executable(test_frame_timer tests/test_frame_timer.cpp)
target_link_libraries(test_frame_timer ${GTEST_LIBRARIES} pthread poincare)

add_test(NAME test_update_logger COMMAND test_update_logger)
add_test(NAME test_frame_timer COMMAND test_frame_timer)
