cmake_minimum_required(VERSION 3.24)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)

add_executable(Minesweeper main.cpp Cell.cpp Board.cpp GameEngine.cpp GameEngine.h random_util.h random_util.cpp Board.h Cell.h)
