cmake_minimum_required(VERSION 3.1)
project(webcat)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11")

add_subdirectory(Http)

add_executable( main_cpp main.cpp )
target_link_libraries(main_cpp Http)

