# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

add_subdirectory(core)
add_subdirectory(manager)
add_subdirectory(protocol)
add_subdirectory(client)
add_subdirectory(probe)
if(QUITE_BUILD_PROBE_QT)
    add_subdirectory(probeqt)
endif()
if(QUITE_BUILD_TEST_API)
    add_subdirectory(testing)
endif()
