cmake_minimum_required(VERSION 3.18.0)

project(snippets
        VERSION 1.0.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Interface library for header-only library
add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}> # Install path for clients
)

# Enable testing and add subdirectories
enable_testing()

# Assuming Catch2 is a submodule or already present in your project
add_subdirectory(lib/Catch2)

# Add test subdirectory
add_subdirectory(test)
