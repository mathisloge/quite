add_executable(cpp_integration_test main.cpp)
add_sanitizers(cpp_integration_test)
target_link_libraries(
    cpp_integration_test
    PRIVATE
        Boost::ut
        quite::test_application_paths
        quite::test
        quite::test_bdd_paths
)
add_test(NAME cpp_integration_test COMMAND cpp_integration_test)

target_sources(cpp_integration_test PRIVATE test_manage_todo.cpp)
