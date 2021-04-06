cmake_minimum_required(VERSION 3.17)
project(Screen)

set(CMAKE_CXX_STANDARD 20)

include_directories(../Models)

include_directories(../global)

include_directories(../Menu)

include_directories(../Store)

include_directories(../consoleUtils)

set(res InterfaceScreen.cpp InterfaceScreen.h Auth/Auth.cpp Auth/Auth.h Launch/Launch.cpp Launch/Launch.h LaunchTaskList/LaunchTaskList.cpp LaunchTaskList/LaunchTaskList.h SpaceshipList/SpaceshipList.cpp SpaceshipList/SpaceshipList.h UserList/UserList.cpp UserList/UserList.h Main/Main.cpp Main/Main.h)

add_library(Screen ${res})

target_link_libraries(Screen cUtils Menu)
