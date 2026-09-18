# File: CMakeLists.txt
# Project: EECS 581 - Project 1: Minesweeper
# Description: CMake configuration defining static UI library, including Qt resource complication (AUTORCC), widget source files, and Qt6::Widgets linkage.
# Author: 
# Creation Date: 2026-09-11

set(CMAKE_AUTORCC ON)
add_library(ui STATIC
    window.cpp
    window.h
    gridwidget.cpp 
    gridwidget.h
    tile.cpp 
    tile.h
    infobar.h 
    infobar.cpp 
    ${CMAKE_SOURCE_DIR}/resources.qrc
)

target_link_libraries(ui PUBLIC Qt6::Widgets)
target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})