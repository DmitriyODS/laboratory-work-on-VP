cmake_minimum_required(VERSION 3.17)
project(Global)

set(CMAKE_CXX_STANDARD 20)

set(res config.cpp config.h)

add_library(Global ${res})
