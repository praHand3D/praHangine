cmake_minimum_required(VERSION 3.20)
project(prahangine CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/glfw)
add_subdirectory(external/googletest)
add_subdirectory(src)
add_subdirectory(sandbox)
add_subdirectory(tests)