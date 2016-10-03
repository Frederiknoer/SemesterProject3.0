cmake_minimum_required(VERSION 3.6)
project(Flag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Frame.h Frame.cpp)
add_executable(Flag ${SOURCE_FILES})