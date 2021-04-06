cmake_minimum_required(VERSION 3.17)
project(Cosmodrome)

set(CMAKE_CXX_STANDARD 20)

include_directories(Store)

include_directories(consoleUtils)

include_directories(Models)

include_directories(ConsoleManager)

include_directories(Menu)

include_directories(Screens)

include_directories(Db)

include_directories(App)

include_directories(global)

add_subdirectory(global)

add_subdirectory(Store)

add_subdirectory(ConsoleManager)

add_subdirectory(Models)

add_subdirectory(consoleUtils)

add_subdirectory(Db)

add_subdirectory(Screens)

add_subdirectory(Menu)

add_subdirectory(App)

add_executable(Cosmodrome main.cpp)

target_link_libraries(Cosmodrome App)
