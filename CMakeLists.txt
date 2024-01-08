cmake_minimum_required(VERSION 3.18.0)
project(snippets-test)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/Catch2)
# These tests can use the Catch2-provided main
add_executable(tests src/test.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# enable_testing()
# add_test(NAME SnippetsTests COMMAND tests.exe)
