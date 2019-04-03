cmake_minimum_required(VERSION 3.13)
project(tree_c C)

set(CMAKE_C_STANDARD 11)

add_executable(tree_c tree.c main.c)


project(tree_cpp CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(tree_cpp tree_cpp.cpp main_cpp.cpp)
