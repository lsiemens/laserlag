# poincare Library

cmake_minimum_required(VERSION 3.10)

project(poincare)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
include_directories(include ${GLFW3_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

add_library(poincare STATIC
    src/update_logger.cpp
    src/frame_timer.cpp
    src/window.cpp
    src/shader.cpp
    src/sprite.cpp)
target_link_libraries(poincare glfw GLEW::glew OpenGL::GL)
target_compile_options(poincare PRIVATE -Wall -Wextra -Wpedantic)

# add examples
add_subdirectory(examples)
add_custom_target(resources ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/examples/resources ${CMAKE_BINARY_DIR}/examples/resources)

# setup tests
enable_testing()
add_subdirectory(tests)
