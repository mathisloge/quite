add_executable(client_test main.cpp)
target_link_libraries(client_test PRIVATE quite::client Boost::ut)
add_test(NAME client_test COMMAND client_test)

#target_sources(client_test PRIVATE
#)
