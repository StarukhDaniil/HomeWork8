cmake_minimum_required(VERSION 3.10)
project(hw8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hw8 main.cpp "sharedPointer.h" "ptrCounter.h")