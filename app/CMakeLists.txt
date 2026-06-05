add_executable(app
    main.cpp
    App.cpp
)

target_link_libraries(app
    PRIVATE prahangine
    PRIVATE pr4
)

add_executable(sandbox
    sandbox.cpp
)

target_link_libraries(sandbox
    PRIVATE prahangine
    PRIVATE pr4
)
