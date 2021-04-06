cmake_minimum_required(VERSION 3.17)
project(cUtils)

set(CMAKE_CXX_STANDARD 20)

set(res consoleUtils.cpp consoleUtils.h)

add_library(cUtils ${res})
