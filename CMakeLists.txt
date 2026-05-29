cmake_minimum_required(VERSION 3.20)
project(prahangine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external/glfw)
add_subdirectory(external/googletest)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(tests)