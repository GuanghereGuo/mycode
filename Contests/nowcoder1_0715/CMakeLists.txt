cmake_minimum_required(VERSION 3.31)
project(nowcoder1_0715)

set(CMAKE_CXX_STANDARD 20)

add_executable(nowcoder1_0715 main.cpp)
add_executable(D D.cpp)
add_executable(test cmake-build-debug/test.cpp)
add_executable(K cmake-build-debug/K.cpp)
