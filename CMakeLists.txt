cmake_minimum_required(VERSION 3.13)
project(data_structures C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.c)
add_executable(src_run ${SOURCE_FILES})

include_directories(src)
add_subdirectory(src)

target_link_libraries(src_run src)
add_subdirectory(test)