cmake_minimum_required(VERSION 3.15)
project(ASD2022_L8_AVL_Tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(AVL-Tree main.cpp parser.cpp parser.h)
add_subdirectory(catch2_tests)