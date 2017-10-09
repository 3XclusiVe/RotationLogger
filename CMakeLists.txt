cmake_minimum_required(VERSION 3.4)
project(RotationLogger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++03")

set(SOURCE_FILES main.cpp RotationLogger/Logger.cpp RotationLogger/Logger.h)
add_executable(RotationLogger ${SOURCE_FILES})