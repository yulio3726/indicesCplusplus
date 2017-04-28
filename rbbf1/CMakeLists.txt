cmake_minimum_required(VERSION 3.7)
project(rbbf1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp funciones.cpp funciones.h structures.h)
add_executable(rbbf1 ${SOURCE_FILES})