add_executable(test_probe_qt main.cpp)
target_link_libraries(test_probe_qt PRIVATE
    Catch2::Catch2
    quite::probeqt
)
catch_discover_tests(test_probe_qt)


target_sources(test_probe_qt PRIVATE
    test_object_tracker.cpp
)
