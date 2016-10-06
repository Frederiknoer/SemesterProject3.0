cmake_minimum_required(VERSION 3.6)
project(Frame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Frame.cpp Frame.h)
add_executable(Frame ${SOURCE_FILES})