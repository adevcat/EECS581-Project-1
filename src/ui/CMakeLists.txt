set(CMAKE_AUTORCC ON)
add_library(ui STATIC
    window.cpp
    window.h
    gridwidget.cpp 
    gridwidget.h
    tile.cpp 
    tile.h
    ${CMAKE_SOURCE_DIR}/resources.qrc
)

target_link_libraries(ui PUBLIC Qt6::Widgets)
target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})