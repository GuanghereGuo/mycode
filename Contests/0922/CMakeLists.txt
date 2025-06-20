cmake_minimum_required(VERSION 3.29)
project(0922)

set(CMAKE_CXX_STANDARD 23)

add_executable(0922 main.cpp)

add_executable(D D.cpp)

add_executable(AA A.cpp)

add_executable(C C.cpp)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")
add_executable(dalao dalao.cpp)