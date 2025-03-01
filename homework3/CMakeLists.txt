cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(BinarySearchTree VERSION 1.0)


add_library(BinarySearchTreeClass STATIC ./BinarySearchTree.cpp ./BinarySearchTree.h)

add_executable(BinarySearchTree main.cpp)

target_link_libraries(BinarySearchTree PUBLIC BinarySearchTreeClass)
