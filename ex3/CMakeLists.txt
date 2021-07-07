cmake_minimum_required(VERSION 3.17)
project(ex3 C)

set(CMAKE_C_STANDARD 11)

add_executable(ex3 main.c DiskManaging.c DiskManaging.h defs.h)