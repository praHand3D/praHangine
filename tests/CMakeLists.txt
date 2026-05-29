add_executable(tests
    math/placeholder.cpp
)

target_link_libraries(tests
    PRIVATE prahangine
    PRIVATE gtest
    PRIVATE gtest_main
)