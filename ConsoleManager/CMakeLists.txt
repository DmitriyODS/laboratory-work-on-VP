cmake_minimum_required(VERSION 3.17)
project(CM)

set(CMAKE_CXX_STANDARD 20)

set(res ConsoleManager.cpp ConsoleManager.h)

add_library(CM ${res})
