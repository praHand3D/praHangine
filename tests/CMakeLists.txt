add_executable(tests
#    math/
)

target_link_libraries(tests
    PRIVATE prahangine
    PRIVATE gtest
    PRIVATE gtest_main
)