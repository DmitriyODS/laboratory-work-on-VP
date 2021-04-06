cmake_minimum_required(VERSION 3.17)
project(Models)

set(CMAKE_CXX_STANDARD 20)

set(res User/User.cpp User/User.h Spaceship/Spaceship.cpp Spaceship/Spaceship.h LaunchTask/LaunchTask.cpp LaunchTask/LaunchTask.h)

add_library(Models ${res})
