cmake_minimum_required(VERSION 3.7)
project(cpp_flocking)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES library.cpp library.h)
add_library(cpp_flocking ${SOURCE_FILES})