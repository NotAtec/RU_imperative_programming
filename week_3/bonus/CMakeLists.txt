cmake_minimum_required(VERSION 3.10)

project(Assignment3_bonus)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp)
target_compile_options(main PRIVATE -Wall -Wextra -pedantic-errors)
