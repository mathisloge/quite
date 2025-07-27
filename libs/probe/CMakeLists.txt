# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_library(probe SHARED)
add_library(quite::probe ALIAS probe)
add_sanitizers(probe)
target_compile_features(probe PUBLIC cxx_std_17 PRIVATE cxx_std_23)
set_target_properties(
    probe
    PROPERTIES POSITION_INDEPENDENT_CODE ON VISIBILITY_INLINES_HIDDEN ON
)
generate_export_header(probe EXPORT_FILE_NAME quite/quite_probe_export.hpp)

target_sources(
    probe
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES include/quite/probe.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_probe_export.hpp
    PRIVATE src/probe.cpp
)
target_link_libraries(probe PRIVATE probeqt)
