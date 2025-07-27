# Copyright (c)
# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

option(SANITIZE_THREAD "Enable ThreadSanitizer for sanitized targets." Off)

set(FLAG_CANDIDATES
    # MSVC uses
    "/fsanitize=thread"
    # GNU/Clang
    "-g -fsanitize=thread"
)

# ThreadSanitizer is not compatible with MemorySanitizer.
if(SANITIZE_THREAD AND SANITIZE_MEMORY)
    message(
        FATAL_ERROR
        "ThreadSanitizer is not compatible with "
        "MemorySanitizer."
    )
endif()

include(sanitize-helpers)

if(SANITIZE_THREAD)
    if(
        NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Linux"
        AND NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin"
    )
        message(
            WARNING
            "ThreadSanitizer disabled for target ${TARGET} because "
            "ThreadSanitizer is supported for Linux systems and macOS only."
        )
        set(SANITIZE_THREAD
            Off
            CACHE BOOL
            "Enable ThreadSanitizer for sanitized targets."
            FORCE
        )
    elseif(NOT ${CMAKE_SIZEOF_VOID_P} EQUAL 8)
        message(
            WARNING
            "ThreadSanitizer disabled for target ${TARGET} because "
            "ThreadSanitizer is supported for 64bit systems only."
        )
        set(SANITIZE_THREAD
            Off
            CACHE BOOL
            "Enable ThreadSanitizer for sanitized targets."
            FORCE
        )
    else()
        sanitizer_check_compiler_flags("${FLAG_CANDIDATES}" "ThreadSanitizer"
            "TSan"
        )
    endif()
endif()

function(add_sanitize_thread TARGET)
    if(NOT SANITIZE_THREAD)
        return()
    endif()

    sanitizer_add_flags(${TARGET} "ThreadSanitizer" "TSan")
endfunction()
