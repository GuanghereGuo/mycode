cmake_minimum_required(VERSION 3.29)
project(Graph)

set(CMAKE_CXX_STANDARD 17)

add_executable(Graph main.cpp)

add_executable(floyd floyd.cpp)

add_executable(P2910 P2910.cpp)

add_executable(Dijkstra Dijkstra.cpp)

add_executable(SPFA SPFA.cpp)

add_executable(SPFA_another SPFA_another.cpp)
