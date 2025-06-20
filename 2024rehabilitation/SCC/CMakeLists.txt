cmake_minimum_required(VERSION 3.29)
project(SCC)

set(CMAKE_CXX_STANDARD 17)

add_executable(SCC main.cpp)

add_executable(B3609Kosaraju B3609Kosaraju.cpp)

add_executable(P3387 "P3387缩点.cpp")
