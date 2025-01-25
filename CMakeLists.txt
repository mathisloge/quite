cmake_minimum_required(VERSION 3.28)
project(quite VERSION 0.0.1 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(CTest)
include(GenerateExportHeader)
include(FeatureSummary)
include(GNUInstallDirs)
include(GetGitRevisionDescription)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(BUILD_SHARED_LIBS ON)

option(QUITE_BUILD_STUDIO "Decides if the GUI should be build" OFF)
add_feature_info(Studio QUITE_BUILD_STUDIO "The studio provides a way to interactivly explore the objects in the app.")
add_feature_info(Testing BUILD_TESTING "Build all tests.")
add_feature_info(SharedLibraries BUILD_SHARED_LIBS "Build all libraries as shared ones.")

get_git_head_revision(git_branch git_sha)
message(STATUS "git_sha: ${git_sha}")
message(STATUS "git_branch: ${git_branch}")

find_package(stdexec CONFIG REQUIRED)
set_package_properties(stdexec PROPERTIES URL "https://github.com/NVIDIA/stdexec" PURPOSE "needed for async code. should be disabled for *hopefully* c++26.")
find_package(quill CONFIG REQUIRED)
set_package_properties(quill PROPERTIES URL "https://github.com/odygrd/quill")
find_package(asio-grpc CONFIG REQUIRED)
set_package_properties(asio-grpc PROPERTIES URL "https://github.com/Tradias/asio-grpc")
find_package(asio CONFIG REQUIRED)
set_package_properties(asio PROPERTIES URL "https://github.com/chriskohlhoff/asio/" PURPOSE "only the pipe object for the process application")
find_package(Stb REQUIRED)
set_package_properties(Stb PROPERTIES URL "https://github.com/nothings/stb" PURPOSE "saving and loading of images")
find_package(nlohmann_json CONFIG REQUIRED)
set_package_properties(nlohmann_json PROPERTIES URL "https://github.com/nlohmann/json")
find_package(EnTT CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(CMakeRC CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Widgets REQUIRED)

add_subdirectory(libs)
add_subdirectory(python)
if(QUITE_BUILD_STUDIO)
    add_subdirectory(studio)
endif()
if(BUILD_TESTING)
    find_package(Catch2 CONFIG REQUIRED)
    add_subdirectory(test)
endif()

feature_summary(WHAT ENABLED_FEATURES DISABLED_FEATURES DESCRIPTION "Features:")
feature_summary(WHAT PACKAGES_FOUND DESCRIPTION "Found packages:")


include(CMakePackageConfigHelpers)

install(TARGETS quite_core quite_logger quite-studio probe quite_protocol
    EXPORT quiteTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET headers
	FILE_SET export_config
)

set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/quite")

install(EXPORT quiteTargets
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

install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/quiteConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/quiteConfigVersion.cmake"
        DESTINATION "${config_install_dir}"
)
