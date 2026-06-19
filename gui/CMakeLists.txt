find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_library(gui
    mainapplication.cpp
    mainapplication.h
)

target_link_libraries(gui
    PUBLIC
        Qt6::Widgets
    PRIVATE
        libcommon
)

target_include_directories(gui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
