file(GLOB TEST_FILES "*.cpp")

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(EXECUTABLE_NAME ${TEST_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${TEST_FILE})
    target_include_directories(${EXECUTABLE_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE Catch2::Catch2WithMain)
    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach()









