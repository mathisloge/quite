# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

add_subdirectory(core)
add_subdirectory(manager)
add_subdirectory(protocol)
add_subdirectory(client)
add_subdirectory(testing)
if(QUITE_BUILD_PROBES)
    add_subdirectory(probeqt)
    add_subdirectory(probe)
endif()
