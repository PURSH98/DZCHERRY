cmake_minimum_required(VERSION 3.10)
project(mtmflix C)

set(CMAKE_C_STANDARD 99)

add_executable(mtmflix
        ${CMAKE_SOURCE_DIR}/newtests/main.c
        ${CMAKE_SOURCE_DIR}/newtests/test_utilities.h
        ${CMAKE_SOURCE_DIR}/newtests/test_utilities_2.h
        list.h
        map.h
        mtm_ex3.h
        mtmflix.c
        mtmflix.h
        series.c
        series.h
        set.h
        user.c
        user.h
        utilities.c
        utilities.h)

target_link_libraries(mtmflix ${CMAKE_SOURCE_DIR}/maclibs/libmtm_ex3.a ${CMAKE_SOURCE_DIR}/maclibs/libmtm.a)
set(CMAKE_C_FLAGS "-std=c99 -Wall -Werror -pedantic-errors -DNDEBUG")

