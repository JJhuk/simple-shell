cmake_minimum_required(VERSION 4.0)
project(simple_shell C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-DLSH_USE_STD_GETLINE)

add_executable(simple_shell main.c
        args/read.c
        args/read.h
        args/split.c
        args/split.h
        launch.c
        launch.h
        process/process.c
        process/process.h
        builtin.c
        builtin.h
        process/pipe.c
        process/pipe.h
)
