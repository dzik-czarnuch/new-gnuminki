cmake_minimum_required(VERSION 3.8)
project(gnuminki)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(main main.cpp bar.cpp bar.h status.cpp status.h changeling.cpp changeling.h game.cpp game.h menu.h square.h board.cpp board.h plant.cpp plant.h areaOfEffect.cpp areaOfEffect.h win.cpp win.h menu.cpp menu.h square.cpp)

target_link_libraries(main ${CURSES_LIBRARIES})

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)
