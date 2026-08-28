# SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

include(GoogleTest)

function(quite_add_test)
    set(options NO_GTEST_MAIN)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES LIBRARIES LABELS)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${oneValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    add_executable(${ARG_NAME} ${ARG_SOURCES})
    add_sanitizers(${ARG_NAME})
    target_link_libraries(
        ${ARG_NAME}
        PRIVATE ${ARG_LIBRARIES} GTest::gtest GTest::gmock
    )
    if(NOT ARG_NO_GTEST_MAIN)
        target_link_libraries(${ARG_NAME} PRIVATE GTest::gtest_main)
    endif()
    gtest_discover_tests(${ARG_NAME} PROPERTIES LABELS "${ARG_LABELS}")
endfunction()
