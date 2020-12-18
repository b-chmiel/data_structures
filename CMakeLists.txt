cmake_minimum_required(VERSION 3.13)
project(data_structures C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(data_structures main.c src/single_linked_list.c src/single_linked_list.h)