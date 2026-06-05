file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*_tests.cpp")

add_executable(tests ${TEST_SOURCES})

target_link_libraries(tests
    PRIVATE prahangine
    PRIVATE gtest
    PRIVATE gtest_main
    PRIVATE pr4
    PRIVATE math
)