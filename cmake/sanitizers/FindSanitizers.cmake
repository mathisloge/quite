# Copyright (c)
# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.13) # target_link_options()

# If any of the used compiler is a GNU compiler, add a second option to static
# link against the sanitizers.
option(SANITIZE_LINK_STATIC "Try to link static against sanitizers." Off)

# Highlight this module has been loaded.
set(Sanitizers_FOUND TRUE)

set(FIND_QUIETLY_FLAG "")
if(DEFINED Sanitizers_FIND_QUIETLY)
    set(FIND_QUIETLY_FLAG "QUIET")
endif()

find_package(ASan ${FIND_QUIETLY_FLAG})
find_package(TSan ${FIND_QUIETLY_FLAG})
find_package(MSan ${FIND_QUIETLY_FLAG})
find_package(UBSan ${FIND_QUIETLY_FLAG})

function(sanitizer_add_blacklist_file FILE)
    if(NOT IS_ABSOLUTE ${FILE})
        set(FILE "${CMAKE_CURRENT_SOURCE_DIR}/${FILE}")
    endif()
    get_filename_component(FILE "${FILE}" REALPATH)

    sanitizer_check_compiler_flags("-fsanitize-blacklist=${FILE}"
        "SanitizerBlacklist" "SanBlist"
    )
endfunction()

function(add_sanitizers)
    # If no sanitizer is enabled, return immediately.
    if(
        NOT (
            SANITIZE_ADDRESS
            OR SANITIZE_MEMORY
            OR SANITIZE_THREAD
            OR SANITIZE_UNDEFINED
        )
    )
        return()
    endif()

    foreach(TARGET ${ARGV})
        # Check if this target will be compiled by exactly one compiler. Other-
        # wise sanitizers can't be used and a warning should be printed once.
        get_target_property(TARGET_TYPE ${TARGET} TYPE)
        if(TARGET_TYPE STREQUAL "INTERFACE_LIBRARY")
            message(
                WARNING
                "Can't use any sanitizers for target ${TARGET}, "
                "because it is an interface library and cannot be "
                "compiled directly."
            )
            return()
        endif()
        sanitizer_target_compilers(${TARGET} TARGET_COMPILER)
        list(LENGTH TARGET_COMPILER NUM_COMPILERS)
        if(NUM_COMPILERS GREATER 1)
            message(
                WARNING
                "Can't use any sanitizers for target ${TARGET}, "
                "because it will be compiled by incompatible compilers. "
                "Target will be compiled without sanitizers."
            )
            return()
        elseif(NUM_COMPILERS EQUAL 0)
            # If the target is compiled by no known compiler, give a warning.
            message(
                WARNING
                "Sanitizers for target ${TARGET} may not be"
                " usable, because it uses no or an unknown compiler. "
                "This is a false warning for targets using only "
                "object lib(s) as input."
            )
        endif()

        # Add sanitizers for target.
        add_sanitize_address(${TARGET})
        add_sanitize_thread(${TARGET})
        add_sanitize_memory(${TARGET})
        add_sanitize_undefined(${TARGET})
    endforeach()
endfunction(add_sanitizers)
