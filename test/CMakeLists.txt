# These tests can use the Catch2-provided main
add_executable(tests test.cpp)

# Include the src directory
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/src)


target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

