add_executable(test_manager_runnable runnable_exe.cpp)
target_link_libraries(test_manager_runnable PRIVATE CLI11::CLI11)
file(GENERATE OUTPUT runnable_path.hpp INPUT runnable_path.in.hpp TARGET test_manager_runnable)
add_library(test_manager_runnable_if INTERFACE)
add_dependencies(test_manager_runnable_if test_manager_runnable)
target_include_directories(test_manager_runnable_if INTERFACE ${CMAKE_CURRENT_BINARY_DIR})


add_executable(test_manager)
target_link_libraries(test_manager PRIVATE
    Catch2::Catch2WithMain
    test_manager_runnable_if
    quite::manager
)
catch_discover_tests(test_manager)


target_sources(test_manager PRIVATE
    test_process_manager.cpp
)
