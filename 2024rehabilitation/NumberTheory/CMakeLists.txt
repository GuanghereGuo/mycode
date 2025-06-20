cmake_minimum_required(VERSION 3.29)
project(NumberTheory)

set(CMAKE_CXX_STANDARD 23)

add_executable(NumberTheory main.cpp)

add_executable(MultiplicativeInverse MultiplicativeInverse.cpp)

add_executable(EuclidAlgorithm EuclidAlgorithm.cpp)
