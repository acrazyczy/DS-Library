cmake_minimum_required(VERSION 3.10.2)
project(DSLib)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O3")
include_directories(
        LinearList
        LinearList/Array
        LinearList/LinkedList
        Stack
        Queue
        Tree
        Tree/BinaryTree
        Tree/Tree
        PriorityQueue
        PriorityQueue/BinaryHeap
        PriorityQueue/LeftistTree
        BST
        TestProgram
        Exception
)
set(src_dir
        Exception/Exception.h
        TestProgram/main.cpp
        LinearList/LinearList.h LinearList/Array/Array.h LinearList/LinkedList/LinkedList.h Queue/Queue.h Stack/Stack.h PriorityQueue/PriorityQueue.h PriorityQueue/BinaryHeap/BinaryHeap.h PriorityQueue/LeftistTree/LeftistTree.h)
add_executable(DSLib ${src_dir})
