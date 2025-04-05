cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(RBTree VERSION 1.0)


add_library(RBTreeClass STATIC ./RBTree/RBTree.cpp ./RBTree/RBTree.h)

add_executable(RBTree main.cpp)

target_link_libraries(RBTree PUBLIC RBTreeClass)
