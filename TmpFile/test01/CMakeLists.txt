cmake_minimum_required(VERSION 3.30)
project(test01)

set(CMAKE_CXX_STANDARD 20)

add_executable(test01 main.cpp)
add_executable(swap swap.c)
add_executable(test02 test02.c)
add_executable(pzy pzy.cpp)
add_executable(binarysearch binarysearch.cpp)
