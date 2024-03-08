# Assuming all your test files are .cpp files
file(GLOB TEST_FILES "*.cpp")

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(EXECUTABLE_NAME ${TEST_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${TEST_FILE})

    # Link against your project library and Catch2
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${PROJECT_NAME} Catch2::Catch2WithMain)

    # Add this executable as a test
    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach()
