set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_executable(probeqt_test)
target_link_libraries(probeqt_test PRIVATE
    Catch2::Catch2WithMain
    asio-grpc::asio-grpc-stdexec
    quite::probeqt
)
catch_discover_tests(probeqt_test)


target_sources(probeqt_test PRIVATE
    test_value_converters.cpp
    test_method_invoker.cpp
    test_qt_meta_registry.cpp
)

#target_compile_options(probeqt_test PRIVATE -fno-omit-frame-pointer -fsanitize=address)
#target_link_options(probeqt_test PRIVATE -fno-omit-frame-pointer -fsanitize=address)
