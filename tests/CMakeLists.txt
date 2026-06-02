add_executable(tests
    math/Matrix.cpp
    assets/PR4_asset_tests.cpp
)

target_link_libraries(tests
    PRIVATE prahangine
    PRIVATE gtest
    PRIVATE gtest_main
)