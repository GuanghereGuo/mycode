cmake_minimum_required(VERSION 3.29)
project(dp)

set(CMAKE_CXX_STANDARD 26)

add_executable(dp main.cpp)

add_executable(PaperMonney PaperMonneyDFS.cpp)

add_executable(PaperMonneyDFS2 PaperMonneyDFS2.cpp)
