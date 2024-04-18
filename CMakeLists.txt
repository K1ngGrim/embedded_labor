cmake_minimum_required(VERSION 3.27)
project(embedded)

set(CMAKE_CXX_STANDARD 17)

add_executable(embedded main.cpp
        async_dma.txt
        main_old.cpp
        perfbench.cpp
)
