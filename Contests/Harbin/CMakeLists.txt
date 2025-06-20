cmake_minimum_required(VERSION 3.29)
project(Harbin)

set(CMAKE_CXX_STANDARD 17)

add_executable(Harbin main.cpp)

add_executable(M M.cpp)
add_executable(C cmake-build-debug/C.cpp)
add_executable(G G.cpp)
add_executable(K K.cpp)