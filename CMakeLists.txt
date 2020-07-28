cmake_minimum_required(VERSION 3.16)
project(excercises C)

set(CMAKE_C_STANDARD 99)

add_executable(excercises lab5/20-1/p2.c)

target_link_libraries(excercises gc)