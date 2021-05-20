cmake_minimum_required(VERSION 3.19)
project(Shell)

set(CMAKE_CXX_STANDARD 20)

include_directories(core)
include_directories(tools/input)

add_executable(Shell
        core/cmd.cpp
        core/cmd.h
        tools/input/read.cpp
        tools/input/read.h
        main.cpp tools/parse/parseCommand.cpp tools/parse/parseCommand.h tools/check/check.cpp tools/check/check.h)
add_executable(testCase test.cpp)
