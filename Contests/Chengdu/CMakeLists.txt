cmake_minimum_required(VERSION 3.29)
project(Chengdu)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3  -Wall")

add_executable(Chengdu main.cpp)
add_executable(A A.cpp)
add_executable(G G.cpp)
add_executable(J J.cpp)
add_executable(I I.cpp)
add_executable(I_test I_test.cpp)
add_executable(B B.cpp)
add_executable(Bself Bself.cpp)
add_executable(K K.cpp)