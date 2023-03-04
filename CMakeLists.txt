cmake_minimum_required(VERSION 3.24)
project(kalkulator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(lib)
include_directories(output)
include_directories(src)

add_executable(kalkulator
        src/equation.cpp
        src/equation.hpp
        src/expression.cpp
        src/expression.hpp
        src/main.cpp
        Makefile)
