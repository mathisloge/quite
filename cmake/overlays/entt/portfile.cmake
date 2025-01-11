vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO skypjack/entt
    REF "6f5e9351ed71ef118507ac1f96a717657d11195f"
    SHA512 be35366b8cbfe154d4a07e719ac2186d1143ec7f414edfd34e40417e32cf4961d1356c3d44c09480f1c76a3c742ce760921a80814b0fd4672df6a151cee35693
    HEAD_REF master
)

set(VCPKG_BUILD_TYPE release) # header-only port

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DENTT_BUILD_TESTING=OFF
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(CONFIG_PATH lib/EnTT/cmake)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/lib")

# Install natvis files
file(INSTALL "${SOURCE_PATH}/natvis/entt" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}/natvis")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
