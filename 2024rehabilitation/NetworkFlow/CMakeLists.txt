cmake_minimum_required(VERSION 3.29)
project(NetworkFlow)

set(CMAKE_CXX_STANDARD 17)

add_executable(NetworkFlow main.cpp)

add_executable(FordFulkerson FordFulkerson.cpp)
add_executable(EdmondsKarp EdmondsKarp.cpp)
add_executable(Dinic Dinic.cpp)