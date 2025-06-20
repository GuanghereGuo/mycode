cmake_minimum_required(VERSION 3.29)
project(bigraph)

set(CMAKE_CXX_STANDARD 20)

add_executable(bigraph main.cpp)

add_executable(BigraphMatch BigraphMatch.cpp)
add_executable(BigraphWeightMatch BigraphWeightMatch.cpp)