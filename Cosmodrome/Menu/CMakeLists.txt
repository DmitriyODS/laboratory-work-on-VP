cmake_minimum_required(VERSION 3.17)
project(Menu)

set(CMAKE_CXX_STANDARD 20)

set(res Menu.cpp Menu.h ItemMenu.cpp ItemMenu.h)

add_library(Menu ${res})
