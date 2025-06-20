cmake_minimum_required(VERSION 3.29)
project(1002)

set(CMAKE_CXX_STANDARD 23)

add_executable(1002 main.cpp)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(L L.cpp)
add_executable(B B.cpp)
add_executable(test test.cpp)
add_executable(_B _B.cpp)
add_executable(Bdp Bdp.cpp)