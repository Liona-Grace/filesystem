cmake_minimum_required(VERSION 3.16)

project(filesystem_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(common)
add_subdirectory(gui)

add_executable(filesystem_app 
    main.cpp
)

target_link_libraries(filesystem_app
    PRIVATE
        gui
)
