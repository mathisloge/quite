add_executable(quite-remote-manager main.cpp)
target_link_libraries(quite-remote-manager PRIVATE CLI11::CLI11 quite::core)
