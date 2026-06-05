file(GLOB_RECURSE PRAHANGINE_SOURCES CONFIGURE_DEPENDS "*.cpp")

add_library(prahangine ${PRAHANGINE_SOURCES})

target_include_directories(prahangine
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(prahangine
    PUBLIC glfw
    PUBLIC glad
    PUBLIC math
    PRIVATE pr4
)
