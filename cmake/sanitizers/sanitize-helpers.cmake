# Copyright (c)
# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

# Helper function to get the language of a source file.
function(sanitizer_lang_of_source FILE RETURN_VAR)
    get_filename_component(LONGEST_EXT "${FILE}" EXT)
    # If extension is empty return. This can happen for extensionless headers
    if("${LONGEST_EXT}" STREQUAL "")
        set(${RETURN_VAR} "" PARENT_SCOPE)
        return()
    endif()
    # Get shortest extension as some files can have dot in their names
    string(REGEX REPLACE "^.*(\\.[^.]+)$" "\\1" FILE_EXT ${LONGEST_EXT})
    string(TOLOWER "${FILE_EXT}" FILE_EXT)
    string(SUBSTRING "${FILE_EXT}" 1 -1 FILE_EXT)

    get_property(ENABLED_LANGUAGES GLOBAL PROPERTY ENABLED_LANGUAGES)
    foreach(LANG ${ENABLED_LANGUAGES})
        list(FIND CMAKE_${LANG}_SOURCE_FILE_EXTENSIONS "${FILE_EXT}" TEMP)
        if(NOT ${TEMP} EQUAL -1)
            set(${RETURN_VAR} "${LANG}" PARENT_SCOPE)
            return()
        endif()
    endforeach()

    set(${RETURN_VAR} "" PARENT_SCOPE)
endfunction()

# Helper function to get compilers used by a target.
function(sanitizer_target_compilers TARGET RETURN_VAR)
    # Check if all sources for target use the same compiler. If a target uses
    # e.g. C and Fortran mixed and uses different compilers (e.g. clang and
    # gfortran) this can trigger huge problems, because different compilers may
    # use different implementations for sanitizers.
    set(BUFFER "")
    get_target_property(TSOURCES ${TARGET} SOURCES)
    foreach(FILE ${TSOURCES})
        # If expression was found, FILE is a generator-expression for an object
        # library. Object libraries will be ignored.
        string(REGEX MATCH "TARGET_OBJECTS:([^ >]+)" _file ${FILE})
        if("${_file}" STREQUAL "")
            sanitizer_lang_of_source(${FILE} LANG)
            if(LANG)
                list(APPEND BUFFER ${CMAKE_${LANG}_COMPILER_ID})
            endif()
        endif()
    endforeach()

    list(APPEND BUFFER ${CMAKE_CXX_COMPILER_ID})
    list(REMOVE_DUPLICATES BUFFER)
    set(${RETURN_VAR} "${BUFFER}" PARENT_SCOPE)
endfunction()

# Helper function to check compiler flags for language compiler.
function(sanitizer_check_compiler_flag FLAG LANG VARIABLE)
    if(${LANG} STREQUAL "C")
        include(CheckCCompilerFlag)
        check_c_compiler_flag("${FLAG}" ${VARIABLE})
    elseif(${LANG} STREQUAL "CXX")
        include(CheckCXXCompilerFlag)
        check_cxx_compiler_flag("${FLAG}" ${VARIABLE})
    elseif(${LANG} STREQUAL "Fortran")
        # CheckFortranCompilerFlag was introduced in CMake 3.x. To be compatible
        # with older Cmake versions, we will check if this module is present
        # before we use it. Otherwise we will define Fortran coverage support as
        # not available.
        include(CheckFortranCompilerFlag OPTIONAL RESULT_VARIABLE INCLUDED)
        if(INCLUDED)
            check_fortran_compiler_flag("${FLAG}" ${VARIABLE})
        elseif(NOT CMAKE_REQUIRED_QUIET)
            message(STATUS "Performing Test ${VARIABLE}")
            message(
                STATUS
                "Performing Test ${VARIABLE}"
                " - Failed (Check not supported)"
            )
        endif()
    endif()
endfunction()

# Helper function to test compiler flags.
function(sanitizer_check_compiler_flags FLAG_CANDIDATES NAME PREFIX)
    set(CMAKE_REQUIRED_QUIET ${${PREFIX}_FIND_QUIETLY})

    get_property(ENABLED_LANGUAGES GLOBAL PROPERTY ENABLED_LANGUAGES)
    foreach(LANG ${ENABLED_LANGUAGES})
        # Sanitizer flags are not dependent on language, but the used compiler.
        # So instead of searching flags foreach language, search flags foreach
        # compiler used.
        set(COMPILER ${CMAKE_${LANG}_COMPILER_ID})
        if(COMPILER AND NOT DEFINED ${PREFIX}_${COMPILER}_FLAGS)
            foreach(FLAG ${FLAG_CANDIDATES})
                if(NOT CMAKE_REQUIRED_QUIET)
                    message(STATUS "Try ${COMPILER} ${NAME} flag = [${FLAG}]")
                endif()

                set(CMAKE_REQUIRED_FLAGS "${FLAG}")
                unset(${PREFIX}_FLAG_DETECTED CACHE)
                sanitizer_check_compiler_flag("${FLAG}" ${LANG}
                    ${PREFIX}_FLAG_DETECTED
                )

                if(${PREFIX}_FLAG_DETECTED)
                    # If compiler is a GNU compiler, search for static flag, if
                    # SANITIZE_LINK_STATIC is enabled.
                    if(SANITIZE_LINK_STATIC AND (${COMPILER} STREQUAL "GNU"))
                        string(TOLOWER ${PREFIX} PREFIX_lower)
                        sanitizer_check_compiler_flag(
                            "-static-lib${PREFIX_lower}" ${LANG}
                            ${PREFIX}_STATIC_FLAG_DETECTED
                        )

                        if(${PREFIX}_STATIC_FLAG_DETECTED)
                            set(FLAG "-static-lib${PREFIX_lower} ${FLAG}")
                        endif()
                    endif()

                    set(${PREFIX}_${COMPILER}_FLAGS
                        "${FLAG}"
                        CACHE STRING
                        "${NAME} flags for ${COMPILER} compiler."
                    )
                    mark_as_advanced(${PREFIX}_${COMPILER}_FLAGS)
                    break()
                endif()
            endforeach()

            if(NOT ${PREFIX}_FLAG_DETECTED)
                set(${PREFIX}_${COMPILER}_FLAGS
                    ""
                    CACHE STRING
                    "${NAME} flags for ${COMPILER} compiler."
                )
                mark_as_advanced(${PREFIX}_${COMPILER}_FLAGS)

                message(
                    WARNING
                    "${NAME} is not available for ${COMPILER} "
                    "compiler. Targets using this compiler will be "
                    "compiled without ${NAME}."
                )
            endif()
        endif()
    endforeach()
endfunction()

# Helper to assign sanitizer flags for TARGET.
function(sanitizer_add_flags TARGET NAME PREFIX)
    # Get list of compilers used by target and check, if sanitizer is available
    # for this target. Other compiler checks like check for conflicting
    # compilers will be done in add_sanitizers function.
    sanitizer_target_compilers(${TARGET} TARGET_COMPILER)

    list(LENGTH TARGET_COMPILER NUM_COMPILERS)
    if("${${PREFIX}_${TARGET_COMPILER}_FLAGS}" STREQUAL "")
        return()
    endif()

    separate_arguments(
        flags_list
        UNIX_COMMAND
        "${${PREFIX}_${TARGET_COMPILER}_FLAGS} ${SanBlist_${TARGET_COMPILER}_FLAGS}"
    )
    target_compile_options(${TARGET} PUBLIC ${flags_list})

    separate_arguments(
        flags_list
        UNIX_COMMAND
        "${${PREFIX}_${TARGET_COMPILER}_FLAGS}"
    )
    target_link_options(${TARGET} PUBLIC ${flags_list})
endfunction()
