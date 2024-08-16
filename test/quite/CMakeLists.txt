cmrc_add_resource_library(testrc ALIAS quite::testrc NAMESPACE testrc
    assets/actual_image.png
    assets/expected_image.png
    assets/diff_image.png
)


add_executable(api_test)
target_link_libraries(api_test PRIVATE
    Catch2::Catch2WithMain
    quite::tester_app
    quite::quite
    spdlog::spdlog
    quite::testrc
)
catch_discover_tests(api_test)


target_sources(api_test PRIVATE
    # process_application.cpp # compile error on gcc-13
    remote_object_test.cpp
    image_diff_test.cpp
)
