cmake_minimum_required(VERSION 3.18)

project(secufile)

set(CMAKE_CXX_STANDARD 20)

add_library(seculib SHARED src/lib.cpp)
add_executable(secufile src/main.cpp)