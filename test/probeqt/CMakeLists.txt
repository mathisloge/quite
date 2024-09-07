add_executable(probeqt_test)
target_link_libraries(probeqt_test PRIVATE
    Catch2::Catch2WithMain
    asio-grpc::asio-grpc-stdexec
    quite::probeqt
)
catch_discover_tests(probeqt_test)


target_sources(probeqt_test PRIVATE
    test_value_converters.cpp
)
