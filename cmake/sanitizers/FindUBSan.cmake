# Copyright (c)
# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

option(
    SANITIZE_UNDEFINED
    "Enable UndefinedBehaviorSanitizer for sanitized targets."
    Off
)

set(FLAG_CANDIDATES
    # MSVC uses
    "/fsanitize=undefined"
    # GNU/Clang
    "-g -fsanitize=undefined"
)

include(sanitize-helpers)

if(SANITIZE_UNDEFINED)
    sanitizer_check_compiler_flags("${FLAG_CANDIDATES}"
        "UndefinedBehaviorSanitizer" "UBSan"
    )
endif()

function(add_sanitize_undefined TARGET)
    if(NOT SANITIZE_UNDEFINED)
        return()
    endif()

    sanitizer_add_flags(${TARGET} "UndefinedBehaviorSanitizer" "UBSan")
endfunction()
