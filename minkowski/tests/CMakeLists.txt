# minkowski Tests
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_point test_point.cpp)
target_link_libraries(test_point ${GTEST_LIBRARIES} pthread minkowski)

add_executable(test_vector test_vector.cpp)
target_link_libraries(test_vector ${GTEST_LIBRARIES} pthread minkowski)

add_executable(test_worldline test_worldline.cpp)
target_link_libraries(test_worldline ${GTEST_LIBRARIES} pthread minkowski)

add_test(NAME test_point COMMAND test_point)
add_test(NAME test_vector COMMAND test_vector)
add_test(NAME test_worldline COMMAND test_worldline)
