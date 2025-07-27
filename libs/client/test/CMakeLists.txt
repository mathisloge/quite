# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

add_executable(client_test main.cpp)
add_sanitizers(client_test)
target_link_libraries(client_test PRIVATE quite::client Boost::ut)
add_test(NAME client_test COMMAND client_test)

#target_sources(client_test PRIVATE
#)
