cmake_minimum_required(VERSION 3.23)
project(connect4_project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS Widgets REQUIRED Core)

add_executable(connect4_project main.cpp MainWindow.cpp GameBoard.h GameBoard.cpp GameConfig.h SettingsDialog.h SettingsDialog.cpp WinDialog.h WinDialog.cpp menu.h menu.cpp GameConfig.cpp)

target_link_libraries(connect4_project PRIVATE Qt6::Widgets Qt6::Core)