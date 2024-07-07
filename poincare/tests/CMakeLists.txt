# poincare Tests

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_update_logger test_update_logger.cpp)
target_link_libraries(test_update_logger ${GTEST_LIBRARIES} pthread poincare)

add_executable(test_frame_timer test_frame_timer.cpp)
target_link_libraries(test_frame_timer ${GTEST_LIBRARIES} pthread poincare)

add_executable(test_window test_window.cpp)
target_link_libraries(test_window ${GTEST_LIBRARIES} pthread poincare)

add_executable(test_shader test_shader.cpp)
target_link_libraries(test_shader ${GTEST_LIBRARIES} pthread poincare)

add_executable(test_sprite test_sprite.cpp)
target_link_libraries(test_sprite ${GTEST_LIBRARIES} pthread poincare)

add_test(NAME test_update_logger COMMAND test_update_logger)
add_test(NAME test_frame_timer COMMAND test_frame_timer)
add_test(NAME test_window COMMAND test_window)
add_test(NAME test_shader COMMAND test_shader)
add_test(NAME test_sprite COMMAND test_sprite)
