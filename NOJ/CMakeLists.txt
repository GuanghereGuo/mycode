cmake_minimum_required(VERSION 3.29)
project(NOJ)

set(CMAKE_CXX_STANDARD 17)

add_link_options(-static)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3  -Wall")

add_executable(NOJ main.cpp)
add_executable(T058 T058.cpp)
add_executable(T059 T059.cpp)
add_executable(T060 T060.cpp)
add_executable(T061 T061.cpp)
add_executable(T062 T062.cpp)
add_executable(T063 T063.cpp)
add_executable(T064 T064.cpp)
add_executable(T065 T065.cpp)
add_executable(T067 T067.cpp)
add_executable(T068 T068.cpp)
add_executable(T070 T070.cpp)
add_executable(T072 T072.cpp)
add_executable(T074 T074.cpp)
add_executable(T075 T075.cpp)
add_executable(T076 T076.cpp)
add_executable(T078 T078.cpp)
add_executable(T079 T079.cpp)
add_executable(T097 T097.cpp)
add_executable(T077 T077.cpp)