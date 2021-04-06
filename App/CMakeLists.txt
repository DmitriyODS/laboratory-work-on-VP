cmake_minimum_required(VERSION 3.17)
project(App)

set(CMAKE_CXX_STANDARD 20)

set(res App.cpp App.h)

include_directories(../Menu)

include_directories(../consoleUtils)

include_directories(../ConsoleManager)

include_directories(../Models)

include_directories(../Screens)

include_directories(../Store)

include_directories(../global)

include_directories(../Db)

add_library(App ${res})

target_link_libraries(App Screen CM Store Global)
