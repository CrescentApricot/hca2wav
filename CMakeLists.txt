cmake_minimum_required(VERSION 3.9)
project(hca2wav)

set(CMAKE_CXX_STANDARD 11)

add_executable(hca2wav
        src/clHCA.cpp
        src/clHCA.h
        main.cpp)
