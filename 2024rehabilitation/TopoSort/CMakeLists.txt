cmake_minimum_required(VERSION 3.29)
project(TopoSort)

set(CMAKE_CXX_STANDARD 17)

add_executable(TopoSort main.cpp)

add_executable(bfs bfs.cpp)
add_executable(dfs dfs.cpp)
add_executable(calculate_all_topo_order calculate_all_topo_order.cpp)