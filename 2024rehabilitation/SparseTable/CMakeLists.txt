cmake_minimum_required(VERSION 3.29)
project(SparseTable)

set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp)

add_executable(SparseTable SparseTable.cpp)