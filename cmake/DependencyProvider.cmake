macro(quite_provide_dependency method dep_name)
    if("${dep_name}" MATCHES "^(Stb)$")
        list(APPEND quite_provider_args ${method} ${dep_name})
        FetchContent_MakeAvailable(stb)
        list(POP_BACK quite_provider_args dep_name method)
        if("${method}" STREQUAL "FIND_PACKAGE")
            set(${dep_name}_FOUND TRUE)
            add_library(stb_fetched INTERFACE)
            add_library(Stb::Stb ALIAS stb_fetched)
            target_include_directories(stb_fetched INTERFACE "$<BUILD_INTERFACE:${stb_SOURCE_DIR}>")
            set(Stb_INCLUDE_DIR "$<BUILD_INTERFACE:${stb_SOURCE_DIR}>")
        elseif(NOT "${dep_name}" STREQUAL "stb")
            FetchContent_SetPopulated(${dep_name}
                SOURCE_DIR "${stb_SOURCE_DIR}"
                BINARY_DIR "${stb_BINARY_DIR}"
            )
        endif()
    endif()
endmacro()
cmake_language(
  SET_DEPENDENCY_PROVIDER quite_provide_dependency
  SUPPORTED_METHODS
    FIND_PACKAGE
    FETCHCONTENT_MAKEAVAILABLE_SERIAL
)
