# minkowski Tests
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_point test_point.cpp)
target_link_libraries(test_point ${GTEST_LIBRARIES} pthread minkowski)

add_executable(test_vector test_vector.cpp)
target_link_libraries(test_vector ${GTEST_LIBRARIES} pthread minkowski)

add_executable(test_world_line test_world_line.cpp)
target_link_libraries(test_world_line ${GTEST_LIBRARIES} pthread minkowski)

add_test(NAME test_point COMMAND test_point)
add_test(NAME test_vector COMMAND test_vector)
add_test(NAME test_world_line COMMAND test_world_line)
