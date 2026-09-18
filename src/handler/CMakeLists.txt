# File: CMakeLists.txt
# Project: EECS 581 - Project 1: Minesweeper
# Description: CMake configuration defining static handler library and configuring include directories and Qt6 widget linking for UI target.
# Author: 
# Creation Date: 2026-09-11

add_library(handler STATIC 
    tileHandler.cpp 
    tileHandler.h
)

target_link_libraries(ui PUBLIC Qt6::Widgets)
target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})