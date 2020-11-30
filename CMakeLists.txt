cmake_minimum_required(VERSION 3.15)
project(Lab_4)

set(CMAKE_CXX_STANDARD 14)
SET(GCC_COVERAGE_COMPILE_FLAGS -pthread -lGL -lGlut -lGLU)

include_directories(.)

add_executable(Lab_4
        ECE_Ghost.cpp
        ECE_Ghost.h
        ECE_Pacman.cpp
        ECE_Pacman.h
        dij.h
        main.cpp
        map.h)
