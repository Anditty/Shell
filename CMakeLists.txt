cmake_minimum_required(VERSION 3.19)
project(Shell)

set(CMAKE_CXX_STANDARD 11)

include_directories(core)
include_directories(tools/input)

add_executable(Shell
        core/cmd.cpp
        core/cmd.h
        tools/input/read.cpp
        tools/input/read.h
        main.cpp tools/parse/parseCommand.cpp tools/parse/parseCommand.h tools/check/check.cpp tools/check/check.h tools/trim/trim.cpp tools/trim/trim.h tools/path/path.cpp tools/path/path.h tools/input/tab.cpp tools/input/tab.h)
add_executable(Test test.cpp
        tools/input/read.cpp
        tools/input/read.h
        tools/trim/trim.h
        tools/trim/trim.cpp)