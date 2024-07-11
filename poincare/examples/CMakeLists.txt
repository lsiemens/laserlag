# poincare Examples

find_package(OpenGL REQUIRED)

file(GLOB EXAMPLE_FILES *.cpp)

foreach(EXAMPLE_SOURCE ${EXAMPLE_FILES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)

    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE poincare glfw ${GLEW_LIBRARIES} ${OPENGLE_LIBRARIES})

    if(${BUILD_EXAMPLES_AS_TESTS})
        add_test(NAME example_${EXAMPLE_NAME} COMMAND ${EXAMPLE_NAME})
        set_tests_properties(example_${EXAMPLE_NAME} PROPERTIES LABELS "examples")
    endif()
endforeach()
