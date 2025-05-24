add_executable(test_probe_qt main.cpp)
target_link_libraries(test_probe_qt PRIVATE quite::probeqt Boost::ut)
add_test(NAME test_probe_qt COMMAND test_probe_qt)

target_sources(test_probe_qt PRIVATE
    test_object_tracker.cpp
    test_method_invoker.cpp
    test_property_collector.cpp
    test_value_containers.cpp
)
