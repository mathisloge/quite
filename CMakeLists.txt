cmake_minimum_required(VERSION 3.28)
file(READ "${CMAKE_SOURCE_DIR}/package.json" PACKAGE_JSON)
string(JSON PACKAGE_JSON_PROJECT_VERSION GET "${PACKAGE_JSON}" version)
string(
    REGEX REPLACE
    "^([0-9]+\\.[0-9]+\\.[0-9]+)-dev\\.([0-9]+)"
    "\\1.\\2"
    BASE_VERSION
    "${PACKAGE_JSON_PROJECT_VERSION}"
)

project(quite VERSION ${BASE_VERSION} LANGUAGES CXX)
message(STATUS "Project version: ${PROJECT_VERSION}")

list(
    APPEND
    CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sanitizers"
)

include(CTest)
include(GenerateExportHeader)
include(FeatureSummary)
include(GNUInstallDirs)
include(GetGitRevisionDescription)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/runtime")

option(QUITE_BUILD_PROBES "Decides if the probes should be build" ON)
add_feature_info(
    Studio
    QUITE_BUILD_STUDIO
    "The studio provides a way to interactively explore the objects in the app."
)
add_feature_info(Testing BUILD_TESTING "Build all tests.")
add_feature_info(
    SharedLibraries
    BUILD_SHARED_LIBS
    "Build all libraries as shared ones."
)

get_git_head_revision(git_branch git_sha)
message(STATUS "git_sha: ${git_sha}")
message(STATUS "git_branch: ${git_branch}")

find_package(Sanitizers REQUIRED)
### NOTE: Set CPM_USE_LOCAL_PACKAGES or CPM_LOCAL_PACKAGES_ONLY to true if you want to use system packages or a package manager like vcpkg.
include(get_cpm)
set(BOOST_VERSION "1.88.0")
list(APPEND BOOST_INCLUDE_LIBRARIES asio process)
cpmaddpackage(
  NAME Boost
  VERSION "${BOOST_VERSION}"
  URL https://github.com/boostorg/boost/releases/download/boost-${BOOST_VERSION}/boost-${BOOST_VERSION}-cmake.tar.xz
  URL_HASH SHA256=f48b48390380cfb94a629872346e3a81370dc498896f16019ade727ab72eb1ec
  EXCLUDE_FROM_ALL ON
  SYSTEM ON
  OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_PROCESS_USE_STD_FS ON" "BOOST_SKIP_INSTALL_RULES ${CMAKE_SKIP_INSTALL_RULES}"
)
cpmaddpackage("gh:fmtlib/fmt#11.2.0")
cpmaddpackage("gh:odygrd/quill@10.0.1")
cpmaddpackage("gh:vector-of-bool/cmrc#952ffddba731fc110bd50409e8d2b8a06abbd237")
cpmaddpackage("gh:skypjack/entt@3.15.0")
cpmaddpackage(URI "gh:CLIUtils/CLI11@2.5.0" OPTIONS "CLI11_PRECOMPILED ON")
cpmaddpackage(URI "gh:NVIDIA/stdexec#0d0a15c669cbd2571248536a7e70524d8b7071aa" OPTIONS "STDEXEC_BUILD_TESTS OFF" "STDEXEC_BUILD_EXAMPLES OFF" "STDEXEC_ENABLE_ASIO ON"
)
cpmaddpackage("gh:Tradias/asio-grpc@3.5.0")
cpmaddpackage("gh:nlohmann/json@3.12.0")
cpmaddpackage("gh:nothings/stb#f0569113c93ad095470c54bf34a17b36646bbbb5")
set(Stb_INCLUDE_DIR "$<BUILD_INTERFACE:${stb_SOURCE_DIR}>")
cpmaddpackage("gh:pybind/pybind11@3.0.0")
if(BUILD_TESTING)
    cpmaddpackage("gh:catchorg/Catch2@3.8.1")
    cpmaddpackage("gh:boost-ext/ut@2.3.1")
endif()
find_package(
    Qt6
    REQUIRED
    COMPONENTS Core Gui Qml Quick Widgets
    REQUIRED
)
find_package(gRPC CONFIG REQUIRED)
if(BUILD_TESTING)
    list(APPEND CMAKE_MODULE_PATH "${Catch2_SOURCE_DIR}/extras")
    include(Catch)
endif()

add_subdirectory(libs)
add_subdirectory(python)
add_subdirectory(remote-manager)
if(BUILD_TESTING)
    add_subdirectory(integration_test)
    add_subdirectory(test)
endif()

feature_summary(WHAT ENABLED_FEATURES DISABLED_FEATURES DESCRIPTION "Features:")
feature_summary(WHAT PACKAGES_FOUND DESCRIPTION "Found packages:")

if(NOT CMAKE_SKIP_INSTALL_RULES)
    include(CMakePackageConfigHelpers)

    install(
        TARGETS
            quite_protocol
            quite_core
            quite_manager
            quite_client
            quite_test
            probe
        EXPORT quiteTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        FILE_SET headers
        FILE_SET export_config
    )

    set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/quite")

    install(
        EXPORT quiteTargets
        FILE quiteTargets.cmake
        NAMESPACE quite::
        DESTINATION "${config_install_dir}"
    )

    configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/quiteConfig.cmake"
        INSTALL_DESTINATION "${config_install_dir}"
    )

    write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/quiteConfigVersion.cmake"
        VERSION "${CMAKE_PROJECT_VERSION}"
        COMPATIBILITY AnyNewerVersion
    )

    install(
        FILES
            "${CMAKE_CURRENT_BINARY_DIR}/quiteConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/quiteConfigVersion.cmake"
        DESTINATION "${config_install_dir}"
    )
endif()
