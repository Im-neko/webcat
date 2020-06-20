cmake_minimum_required(VERSION 3.1)
project(webcat)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS "-pthread")

add_subdirectory(Http)
add_subdirectory(lib)
add_executable( main_cpp main.cpp )
target_link_libraries(main_cpp Http Lib)

