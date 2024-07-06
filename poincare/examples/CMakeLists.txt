# poincare Examples

find_package(OpenGL REQUIRED)

add_executable(window_example window_example.cpp)
target_link_libraries(window_example poincare glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})

add_executable(two_windows_example two_windows_example.cpp)
target_link_libraries(two_windows_example poincare glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
