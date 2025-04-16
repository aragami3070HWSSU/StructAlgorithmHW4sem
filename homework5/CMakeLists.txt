cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AVLTree VERSION 1.0)


add_library(AVLTreeClass STATIC ./AVLTree/AVLTree.cpp ./AVLTree/AVLTree.h)

add_executable(AVLTree main.cpp)

target_link_libraries(AVLTree PUBLIC AVLTreeClass)
