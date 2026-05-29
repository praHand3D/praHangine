add_library(prahangine
    prahangine.cpp
)

target_include_directories(prahangine
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(prahangine
    PUBLIC glfw
)