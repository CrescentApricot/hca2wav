cmake_minimum_required(VERSION 3.9)
project(hca2wav)

set(CMAKE_CXX_STANDARD 11)
include(cmake/flags.c++.std.cmake)

add_executable(
        hca2wav
        main.cpp
        src/clHCA.cpp
        include/clHCA.h
)
