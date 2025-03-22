include(FetchContent)

macro(fetch_and_use_vcpkg)
    include(FetchContent)
    FetchContent_Declare(vcpkg
        GIT_REPOSITORY https://github.com/microsoft/vcpkg/
        GIT_TAG a7d06b3a72d5ec48353bacb84152bd027ee9999b
    )
    FetchContent_MakeAvailable(vcpkg)
    set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake" CACHE FILEPATH "")
endmacro()
