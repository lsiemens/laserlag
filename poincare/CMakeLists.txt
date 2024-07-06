cmake_minimum_required(VERSION 3.10)

project(poincare)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
include_directories(include ${GLEW_INCLUDE_DIRS})

add_library(poincare STATIC
    src/update_logger.cpp
    src/frame_timer.cpp
    src/window.cpp
    src/shader.cpp)
target_link_libraries(poincare glfw ${GLEW_LIBRARIES})

# setup tests
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_update_logger tests/test_update_logger.cpp)
target_link_libraries(test_update_logger ${GTEST_LIBRARIES} pthread poincare)

add_executable(test_frame_timer tests/test_frame_timer.cpp)
target_link_libraries(test_frame_timer ${GTEST_LIBRARIES} pthread poincare)

add_executable(test_window tests/test_window.cpp)
target_link_libraries(test_window ${GTEST_LIBRARIES} pthread poincare)

add_executable(test_shader tests/test_shader.cpp)
target_link_libraries(test_shader ${GTEST_LIBRARIES} pthread poincare)

add_test(NAME test_update_logger COMMAND test_update_logger)
add_test(NAME test_frame_timer COMMAND test_frame_timer)
add_test(NAME test_window COMMAND test_window)
add_test(NAME test_shader COMMAND test_shader)
