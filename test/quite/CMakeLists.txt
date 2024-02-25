add_executable(api_test)
target_link_libraries(api_test PRIVATE Catch2::Catch2WithMain quite::tester_app quite::quite uvw::uvw)
catch_discover_tests(api_test)


target_sources(api_test PRIVATE
    process_application.cpp
)
