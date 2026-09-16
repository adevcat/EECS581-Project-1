
add_library(handler STATIC 
    tileHandler.cpp 
    tileHandler.h
)

target_link_libraries(ui PUBLIC Qt6::Widgets)
target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})