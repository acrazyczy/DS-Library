cmake_minimum_required(VERSION 3.10.2)
project(DSLib)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -g")
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
        PriorityQueue/SkewHeap
        PriorityQueue/BinomialHeap
        BinarySearchTree
        BinarySearchTree/AVLTree
        TestProgram
        Exception
        Iterator
)
set(src_dir
        Exception/Exception.h
        TestProgram/main.cpp
        LinearList/LinearList.h LinearList/Array/Array.h LinearList/LinkedList/LinkedList.h Queue/Queue.h Stack/Stack.h PriorityQueue/PriorityQueue.h PriorityQueue/BinaryHeap/BinaryHeap.h PriorityQueue/LeftistTree/LeftistTree.h PriorityQueue/SkewHeap/SkewHeap.h PriorityQueue/BinomialHeap/BinomialHeap.h BinarySearchTree/AVLTree/AVLTree.h Iterator/Iterator.h)
add_executable(DSLib ${src_dir})
