add_executable(test_protocol)
target_link_libraries(test_protocol PRIVATE
    Catch2::Catch2WithMain
    quite::protocol
)
catch_discover_tests(test_protocol)


target_sources(test_protocol PRIVATE
    test_value.cpp
)
