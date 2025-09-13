# SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
#
# SPDX-License-Identifier: MIT

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
include(CMakeDependentOption)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/runtime")

option(QUITE_BUILD_PROBE_QT "Decides if the probes should be build" ON)
option(QUITE_BUILD_TEST_API "Decides if the testing API should be build" ON)
cmake_dependent_option(
    QUITE_BUILD_PYTHON_TEST_API
    "Decides if the python testing API should be build"
    ON
    BUILD_TEST_API
    OFF
)
option(
    QUITE_BUILD_REMOTE_MANAGER
    "Decides if the remote manager should be build"
    ON
)

add_feature_info(QtProbe QUITE_BUILD_PROBE_QT "Build probeqt")
add_feature_info(TestingApi QUITE_BUILD_TEST_API "Build testing API")
add_feature_info(
    TestingPythonApi
    QUITE_BUILD_PYTHON_TEST_API
    "Build testing API"
)
add_feature_info(
    RemoteManager
    QUITE_BUILD_REMOTE_MANAGER
    "Build remote manager"
)

add_feature_info(Testing BUILD_TESTING "Build all tests")
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
set(BOOST_VERSION "1.89.0")
list(APPEND BOOST_INCLUDE_LIBRARIES asio process)
cpmaddpackage(
  NAME Boost
  VERSION "${BOOST_VERSION}"
  URL https://github.com/boostorg/boost/releases/download/boost-${BOOST_VERSION}/boost-${BOOST_VERSION}-cmake.tar.xz
  URL_HASH SHA256=67acec02d0d118b5de9eb441f5fb707b3a1cdd884be00ca24b9a73c995511f74
  EXCLUDE_FROM_ALL ON
  SYSTEM ON
  FIND_PACKAGE_ARGUMENTS "CONFIG"
  OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_PROCESS_USE_STD_FS ON" "BOOST_SKIP_INSTALL_RULES ${CMAKE_SKIP_INSTALL_RULES}"
)
cpmaddpackage("gh:fmtlib/fmt#11.2.0")
cpmaddpackage("gh:odygrd/quill@10.1.0")
cpmaddpackage(URI "gh:skypjack/entt@3.15.0" NAME "EnTT" FIND_PACKAGE_ARGUMENTS "CONFIG")
cpmaddpackage(URI "gh:NVIDIA/stdexec#daf12bcc46438f88b3c78212363f7b6531338780" NAME "stdexec" VERSION 0.11 FIND_PACKAGE_ARGUMENTS "CONFIG" OPTIONS "STDEXEC_BUILD_TESTS OFF" "STDEXEC_BUILD_EXAMPLES OFF" "STDEXEC_ENABLE_ASIO ON"
)
cpmaddpackage(URI "gh:Tradias/asio-grpc@3.5.0" FIND_PACKAGE_ARGUMENTS "CONFIG" VERSION 3.4.0)
cpmaddpackage(URI "gh:nlohmann/json@3.12.0" FIND_PACKAGE_ARGUMENTS "CONFIG" NAME "nlohmann_json")
cpmaddpackage(URI "gh:nothings/stb#f0569113c93ad095470c54bf34a17b36646bbbb5" NAME Stb
)
if(QUITE_BUILD_REMOTE_MANAGER OR BUILD_TESTING)
    cpmaddpackage(URI "gh:CLIUtils/CLI11@2.5.0" OPTIONS "CLI11_PRECOMPILED ON")
endif()
set(Stb_INCLUDE_DIR "$<BUILD_INTERFACE:${Stb_SOURCE_DIR}>")
if(BUILD_TESTING)
    cpmaddpackage("gh:vector-of-bool/cmrc#952ffddba731fc110bd50409e8d2b8a06abbd237"
    )
    cpmaddpackage("gh:boost-ext/ut@2.3.1")
endif()

if(QUITE_BUILD_PROBE_QT)
    find_package(
        Qt6
        REQUIRED
        COMPONENTS Core Gui Qml Quick Widgets
        REQUIRED
    )
endif()
find_package(gRPC CONFIG REQUIRED)

add_subdirectory(libs)
if(BUILD_TESTING)
    add_subdirectory(simple_tester)
endif()

if(QUITE_BUILD_PYTHON_TEST_API)
    cpmaddpackage(URI "gh:pybind/pybind11@3.0.1" FIND_PACKAGE_ARGUMENTS "CONFIG" VERSION 3.0.0)
    add_subdirectory(python)
endif()

if(QUITE_BUILD_REMOTE_MANAGER)
    add_subdirectory(remote-manager)
endif()
if(BUILD_TESTING)
    add_subdirectory(example)
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
            probe_qt
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
