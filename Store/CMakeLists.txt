cmake_minimum_required(VERSION 3.17)
project(Store)

set(CMAKE_CXX_STANDARD 20)

set(res State.cpp State.h Store.cpp Store.h Action.cpp Action.h ActionTypes.cpp ActionTypes.h)

include_directories(../Screens)

include_directories(../Models)

include_directories(../Db)

add_library(Store ${res})

target_link_libraries(Store Models Db)
