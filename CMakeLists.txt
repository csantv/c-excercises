cmake_minimum_required(VERSION 3.16)
project(excercises C)

set(CMAKE_C_STANDARD 99)

add_executable(excercises lab2-tad/p1.c lab2-tad/p1.h)

target_link_libraries(excercises gc)