# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

add_executable(quite-remote-manager main.cpp)
target_link_libraries(quite-remote-manager PRIVATE CLI11::CLI11 quite::core)
