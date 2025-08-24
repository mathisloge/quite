# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

add_subdirectory(impl)

add_library(probe_qt)
add_library(quite::probe_qt ALIAS probe_qt)
add_sanitizers(probe_qt)
target_compile_features(probe_qt PUBLIC cxx_std_17 PRIVATE cxx_std_23)
set_target_properties(
    probe_qt
    PROPERTIES POSITION_INDEPENDENT_CODE ON VISIBILITY_INLINES_HIDDEN ON
)
generate_export_header(
    probe_qt
    EXPORT_FILE_NAME quite/quite_probe_qt_export.hpp
)

target_link_libraries(
    probe_qt
    PUBLIC quite::probe
    PRIVATE quite::core quite::protocol
)

target_include_directories(probe_qt PRIVATE impl)
target_sources(
    probe_qt
    PUBLIC
        FILE_SET headers
            TYPE HEADERS
            BASE_DIRS include
            FILES include/quite/probe_qt/probe_qt.hpp
        FILE_SET export_config
            TYPE HEADERS
            BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
            FILES ${CMAKE_CURRENT_BINARY_DIR}/quite/quite_probe_qt_export.hpp
    PRIVATE src/probe_qt.cpp $<TARGET_OBJECTS:probe_qt_impl>
)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
