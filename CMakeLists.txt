cmake_minimum_required(VERSION 3.19)
project(Shell)

set(CMAKE_CXX_STANDARD 14)

include_directories(core)
include_directories(tools/input)

add_executable(Shell
        core/cmd.cpp
        core/cmd.h
        tools/input/read.cpp
        tools/input/read.h
        main.cpp)
