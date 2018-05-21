cmake_minimum_required(VERSION 3.10)
project(map_mtm C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(map_mtm
        map_mtm.c
        map_mtm.h)
