cmake_minimum_required(VERSION 3.29)
project(lca)

set(CMAKE_CXX_STANDARD 20)

add_executable(lca main.cpp)

add_executable("sp" "树剖.cpp")
add_executable(bzm "倍增.cpp")
add_executable(tarjan tarjan.cpp)
add_executable(sp2 sp2.cpp)