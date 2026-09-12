cmake_minimum_required(VERSION 3.16)
 
project(minesweeper VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
 
find_package(Qt6 REQUIRED COMPONENTS Widgets)
 
qt_standard_project_setup()
 
add_subdirectory(src/app)
add_subdirectory(src/ui)
