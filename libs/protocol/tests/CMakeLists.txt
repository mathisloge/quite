add_executable(test_protocol main.cpp)
add_sanitizers(test_protocol)
target_link_libraries(test_protocol PRIVATE quite::protocol Boost::ut)
add_test(NAME test_protocol COMMAND test_protocol)

target_sources(test_protocol PRIVATE test_server.cpp)
