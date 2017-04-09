cmake_minimum_required(VERSION 2.8)
project(dsa162a2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp eventLib.cpp dbLib.cpp processData.cpp)
add_executable(dsa162a2 ${SOURCE_FILES})