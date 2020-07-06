cmake_minimum_required(VERSION 3.16)
project(excercises C)

set(CMAKE_C_STANDARD 99)

add_executable(excercises bt/caballo.c bt/caballo.h)

target_link_libraries(excercises gc)