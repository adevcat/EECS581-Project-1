qt_add_executable(minesweeper
    main.cpp
)

target_link_libraries(minesweeper PRIVATE Qt6::Widgets)

set_target_properties(minesweeper PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)