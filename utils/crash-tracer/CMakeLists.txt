add_executable(crash-tracer main.cpp)
target_link_libraries(crash-tracer PRIVATE cpptrace::cpptrace)
