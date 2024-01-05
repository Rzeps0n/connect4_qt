cmake_minimum_required(VERSION 3.23)
project(connect4_project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#find_package(Qt6 COMPONENTS Widgets REQUIRED)

#add_executable(connect4_project main.cpp mainwindow.cpp)

#target_link_libraries(connect4_project PRIVATE Qt6::Widgets)


find_package(Qt6 COMPONENTS Widgets REQUIRED Core)

add_executable(connect4_project main.cpp mainwindow.cpp)

target_link_libraries(connect4_project PRIVATE Qt6::Widgets Qt6::Core)