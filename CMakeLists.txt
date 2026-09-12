set(Qt6_DIR "C:\\Qt\\6.11.2\\mingw_64\\lib\\cmake\\Qt6")

cmake_minimum_required(VERSION 3.16)

project(minesweeper VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_subdirectory(src/app)


