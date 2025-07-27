# Copyright (c)
# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

option(SANITIZE_ADDRESS "Enable AddressSanitizer for sanitized targets." Off)

set(FLAG_CANDIDATES
    # MSVC uses
    "/fsanitize=address"
    # Clang 3.2+ use this version. The no-omit-frame-pointer option is optional.
    "-g -fsanitize=address -fno-omit-frame-pointer"
    "-g -fsanitize=address"
    # Older deprecated flag for ASan
    "-g -faddress-sanitizer"
)

if(SANITIZE_ADDRESS AND (SANITIZE_THREAD OR SANITIZE_MEMORY))
    message(
        FATAL_ERROR
        "AddressSanitizer is not compatible with "
        "ThreadSanitizer or MemorySanitizer."
    )
endif()

include(sanitize-helpers)

if(SANITIZE_ADDRESS)
    sanitizer_check_compiler_flags("${FLAG_CANDIDATES}" "AddressSanitizer"
        "ASan"
    )

    find_program(ASan_WRAPPER "asan-wrapper" PATHS ${CMAKE_MODULE_PATH})
    mark_as_advanced(ASan_WRAPPER)
endif()

function(add_sanitize_address TARGET)
    if(NOT SANITIZE_ADDRESS)
        return()
    endif()

    sanitizer_add_flags(${TARGET} "AddressSanitizer" "ASan")
endfunction()
