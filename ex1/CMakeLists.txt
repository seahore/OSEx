# cmake_minimum_required(VERSION <specify CMake version here>)
project(ex1 C)

set(CMAKE_C_STANDARD 11)

add_executable(ex1 main.c PCB.c PCB.h defs.h)