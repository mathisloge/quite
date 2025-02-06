vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO skypjack/entt
    REF "476822e6c4abf2b1f3d212e6296c1d9d411ff8e8"
    SHA512 9269bf00445451b283eab746eafb44dcf06773b1b9116a47dd0969360448aaf7063c01e31dffa9e7e791aef3cd316e5b0740a6d804b12f62beb3c7a920577930
    HEAD_REF master
)

set(VCPKG_BUILD_TYPE release) # header-only port

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DENTT_BUILD_TESTING=OFF
        -DENTT_INSTALL=ON
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(CONFIG_PATH lib/EnTT/cmake)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/lib")

# Install natvis files
file(INSTALL "${SOURCE_PATH}/natvis/entt" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}/natvis")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
