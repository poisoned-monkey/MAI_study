cmake_minimum_required(VERSION 3.12.3)
project(laba1_home)

add_executable(laba1_home main.cpp Rectangle.cpp)

set_property(TARGET laba1_home PROPERTY CXX_STANDART 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -v")



