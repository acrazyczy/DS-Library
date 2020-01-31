cmake_minimum_required(VERSION 3.10.2)
project(DSLib)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g")
include_directories(
        LinearList
        LinearList/Array
        Stack
        Queue
        Tree
        Heap
        BST
        TestProgram
)
set(src_dir
        TestProgram/main.cpp
        LinearList/LinearList.h LinearList/Array/Array.h)
add_executable(DSLib ${src_dir})
