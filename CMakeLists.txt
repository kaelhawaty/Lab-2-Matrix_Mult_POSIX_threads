cmake_minimum_required(VERSION 3.17)
project(multp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

include_directories(.)

add_executable(multp
        compute.c
        header.h
        io_utils.c
        main.c)
