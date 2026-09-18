# File: CMakeLists.txt
# Project: EECS 581 - Project 1: Minesweeper
# Description: CMake configuration creating main executable (minesweeper), linking Qt6::Widgets and the static UI library, and setting up post-build Windows deployment (windeployqt) and ZIP packaging.
# Author: 
# Creation Date: 2026-09-11

qt_add_executable(minesweeper
    main.cpp
)

target_link_libraries(minesweeper PRIVATE Qt6::Widgets ui)

# automatically adds neccessary dll files for app
if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${Qt6_DIR}/../../../bin")
    # run windeployqt, executable that automatically finds and bundles dependencies for windows
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET minesweeper POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:minesweeper>"
            COMMENT "Running windeployqt..."
        )
        # zips files
        add_custom_command(TARGET minesweeper POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E tar cf
                "${CMAKE_BINARY_DIR}/minesweeper.zip" --format=zip
                --
                "."
            WORKING_DIRECTORY "$<TARGET_FILE_DIR:minesweeper>"
        )
    endif()
endif()