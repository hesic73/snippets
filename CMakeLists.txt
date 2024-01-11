cmake_minimum_required(VERSION 3.18.0)

project(snippets
LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(src)

add_subdirectory(lib/Catch2)
add_subdirectory(test)

