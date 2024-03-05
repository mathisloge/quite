add_executable(api_test)
target_link_libraries(api_test PRIVATE Catch2::Catch2WithMain quite::tester_app quite::protocol quite::quite spdlog::spdlog)
catch_discover_tests(api_test)


target_sources(api_test PRIVATE
    process_application.cpp
)
