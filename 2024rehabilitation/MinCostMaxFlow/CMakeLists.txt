cmake_minimum_required(VERSION 3.29)
project(MinCostMaxFlow)

set(CMAKE_CXX_STANDARD 17)

add_executable(MinCostMaxFlow main.cpp)

add_executable(DinicSSP DinicSSP.cpp)