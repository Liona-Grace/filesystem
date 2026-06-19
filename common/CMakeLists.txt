add_library(libcommon
    filecontroller.cpp
    filecontroller.h
    nlohmann/json.hpp
)

target_include_directories(libcommon PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
