add_library(prahangine
    prahangine.cpp
    pr4/AssetSystem.cpp
    math/Matrix.cpp
    utils/createCube.cpp
    config.cpp
    render/shaders.cpp
    render/Renderer.cpp
)

target_include_directories(prahangine
    PUBLIC ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(prahangine
    PUBLIC glfw
    PUBLIC glad
)