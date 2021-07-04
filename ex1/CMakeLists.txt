# cmake_minimum_required(VERSION <specify CMake version here>)
project(experiment C)

set(CMAKE_C_STANDARD 11)

add_executable(experiment main.c PCB.c PCB.h defs.h)