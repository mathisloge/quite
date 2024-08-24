set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(meta_test)
target_link_libraries(meta_test PRIVATE
    Catch2::Catch2WithMain
    fmt::fmt
    quite::protocol
    Qt6::Core
)
catch_discover_tests(meta_test)


target_sources(meta_test PRIVATE
    test_object_registry.cpp
)
