cmake_minimum_required(VERSION 3.2)

project(test_main)

# Global CMake options:
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(test_main test.cpp core.cpp)

enable_testing()
add_test(NAME test_main COMMAND test_main)
