cmake_minimum_required(VERSION 3.7)
project(permutations)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp funciones.cpp funciones.h structures.h)
add_executable(permutations ${SOURCE_FILES})