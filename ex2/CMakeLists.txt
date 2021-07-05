cmake_minimum_required(VERSION 3.17)
project(ex2 C)

set(CMAKE_C_STANDARD 11)

add_executable(ex2 main.c FreePartition.c FreePartition.h defs.h)