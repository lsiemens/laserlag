# poincare Library

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
add_subdirectory(tests)
