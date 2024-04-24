cmake_minimum_required(VERSION 3.27)
project(embedded)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(embedded main.cpp
        gps_sequence_7.txt
)

add_executable(
        not_optimized
        main_old.cpp
)
