cmake_minimum_required(VERSION 3.23)
project(Connect4)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#set(CMAKE_PREFIX_PATH "C:/Qt/6.2.4/mingw_64/lib/cmake")

find_package(Qt6 COMPONENTS Widgets REQUIRED Core)

add_executable(Connect4 main.cpp MainWindow.cpp GameBoard.h GameBoard.cpp GameConfig.h SettingsDialog.h SettingsDialog.cpp WinDialog.h WinDialog.cpp menu.h menu.cpp GameConfig.cpp)
#add_executable(Connect4 MACOSX_BUNDLE main.cpp MainWindow.cpp GameBoard.h GameBoard.cpp GameConfig.h SettingsDialog.h SettingsDialog.cpp WinDialog.h WinDialog.cpp menu.h menu.cpp GameConfig.cpp)

target_link_libraries(Connect4 PRIVATE Qt6::Widgets Qt6::Core)

set_target_properties(Connect4 PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in)

