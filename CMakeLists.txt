cmake_minimum_required(VERSION 3.16)

project(main)

# Global CMake options:
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(main main.cpp)

install(TARGETS main)

enable_testing()
add_test(NAME custom_test_name COMMAND main)