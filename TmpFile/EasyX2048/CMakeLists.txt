cmake_minimum_required(VERSION 3.30)
project(2048 CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

include_directories(./EasyX/include)
link_directories(./EasyX/lib64)
link_libraries(libeasyx.a)

add_executable(2048
        game_logic.h
        game_logic.cpp
        game_draw.h
        game_draw.cpp
        main.cpp)
