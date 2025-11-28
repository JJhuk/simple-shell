cmake_minimum_required(VERSION 4.0)
project(simple_shell C)

set(CMAKE_C_STANDARD 11)

add_executable(simple_shell main.c
        loop.h
        loop.c
        read.c
        read.h
        split.c
        split.h
        launch.c
        launch.h
        builtins.c
        builtins.h
)
