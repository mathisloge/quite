add_executable(core_test main.cpp)
add_sanitizers(core_test)
target_link_libraries(core_test PRIVATE quite::core Boost::ut)
add_test(NAME core_test COMMAND core_test)

target_sources(core_test PRIVATE test_error.cpp)
