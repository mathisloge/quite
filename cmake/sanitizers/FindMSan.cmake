# Copyright (c)
# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

option(SANITIZE_MEMORY "Enable MemorySanitizer for sanitized targets." Off)

set(FLAG_CANDIDATES
    # MSVC uses
    "/fsanitize=memory"
    # GNU/Clang
    "-g -fsanitize=memory"
)

include(sanitize-helpers)

if(SANITIZE_MEMORY)
    if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        message(
            WARNING
            "MemorySanitizer disabled for target ${TARGET} because "
            "MemorySanitizer is supported for Linux systems only."
        )
        set(SANITIZE_MEMORY
            Off
            CACHE BOOL
            "Enable MemorySanitizer for sanitized targets."
            FORCE
        )
    elseif(NOT ${CMAKE_SIZEOF_VOID_P} EQUAL 8)
        message(
            WARNING
            "MemorySanitizer disabled for target ${TARGET} because "
            "MemorySanitizer is supported for 64bit systems only."
        )
        set(SANITIZE_MEMORY
            Off
            CACHE BOOL
            "Enable MemorySanitizer for sanitized targets."
            FORCE
        )
    else()
        sanitizer_check_compiler_flags("${FLAG_CANDIDATES}" "MemorySanitizer"
            "MSan"
        )
    endif()
endif()

function(add_sanitize_memory TARGET)
    if(NOT SANITIZE_MEMORY)
        return()
    endif()

    sanitizer_add_flags(${TARGET} "MemorySanitizer" "MSan")
endfunction()
