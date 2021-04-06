cmake_minimum_required(VERSION 3.17)
project(Db)

set(CMAKE_CXX_STANDARD 20)

set(res Db.cpp Db.h)

add_library(Db ${res})
