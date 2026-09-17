cmake_minimum_required(VERSION 3.16)

project(minesweeper VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

# Board Manager + Game Logic. No Qt linkage on purpose.
add_library(core STATIC
    board.cpp
    board.h
    cell.h
    logicHandler.cpp
    logicHandler.h
)

# Anything linking `core` can include "board.h" / "logicHandler.h" directly.
target_include_directories(core PUBLIC ${CMAKE_SOURCE_DIR})

# qt_standard_project_setup() turns AUTOMOC/AUTOUIC on for every target, but
# `core` contains no Q_OBJECT classes and no Qt headers at all, so running the
# meta-object compiler over it does nothing except add a fragile build step.
# Turning it off here removes that step and speeds up the build.
set_target_properties(core PROPERTIES
    AUTOMOC OFF
    AUTOUIC OFF
    AUTORCC OFF
)

add_subdirectory(src)
add_subdirectory(src/ui)
