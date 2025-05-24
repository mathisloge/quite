cmrc_add_resource_library(testrc ALIAS quite::testrc NAMESPACE testrc
    assets/actual_image.png
    assets/expected_image.png
    assets/diff_image.png
)

add_executable(api_test)
target_link_libraries(
    api_test
    PUBLIC
        Catch2::Catch2WithMain
        quite::tester_app
        quite::client
        quite::core
        quite::testrc
)
target_include_directories(api_test PRIVATE ${Stb_INCLUDE_DIR})
catch_discover_tests(api_test)

target_sources(
    api_test
    PRIVATE
        #process_application.cpp # compile error on gcc-13
        #remote_object_test.cpp
        test_probe_manager.cpp
    #image_diff_test.cpp
    #meta_test.cpp
)
