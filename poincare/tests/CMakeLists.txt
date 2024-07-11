# poincare Tests

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

file(GLOB TEST_FILES *.cpp)

foreach(TEST_SOURCE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES} pthread poincare minkowski)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
