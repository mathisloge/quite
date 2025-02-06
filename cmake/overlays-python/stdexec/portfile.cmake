set(VCPKG_BUILD_TYPE release) # header-only

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO mathisloge/stdexec
    REF d1e153a07dbf3529c140436e261d34563e422fa5
    SHA512 5f89ec4ae79f192a79422dce7b7620b515610f154bf52fc11d242b362b8a21d6b4ecafb8cbfe3db65ff30bfc9a91b1184001f7b6ef0b64a70e3fbd9e15b718ae
    HEAD_REF main
)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH_RAPIDS
    REPO rapidsai/rapids-cmake
    REF v24.02.01 # stable tag (stdexec wants branch-24.02)
    SHA512 bb8f2b1177f6451d61f2de26f39fd6d31c2f0fb80b4cd1409edc3e6e4f726e80716ec177d510d0f31b8f39169cd8b58290861f0f217daedbd299e8e426d25891
    HEAD_REF main
)
vcpkg_replace_string("${SOURCE_PATH}/CMakeLists.txt"
    [[file(DOWNLOAD https://raw.githubusercontent.com/rapidsai/rapids-cmake/branch-24.02/RAPIDS.cmake]]
    "file(COPY_FILE \"${SOURCE_PATH_RAPIDS}/RAPIDS.cmake\""
)

# stdexec uses cpm (via rapids-cmake).
# Setup a local cpm cache from assets cached by vcpkg
file(REMOVE_RECURSE "${CURRENT_BUILDTREES_DIR}/cpm")
# Version from rapids-cmake cpm/detail/download.cmake
set(CPM_DOWNLOAD_VERSION 0.38.5)
vcpkg_download_distfile(CPM_CMAKE
    URLS https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
    FILENAME CPM_${CPM_DOWNLOAD_VERSION}.cmake
    SHA512 a376162be4fe70408c000409f7a3798e881ed183cb51d57c9540718fdd539db9028755653bd3965ae7764b5c3e36adea81e0752fe85e40790f022fa1c4668cc6
)
file(INSTALL "${CPM_CMAKE}" DESTINATION "${CURRENT_BUILDTREES_DIR}/cpm/cpm")

# Version and patch from stdexec CMakeLists.txt
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH_ICM
    REPO iboB/icm
    REF v1.5.0 # from stdexec CMakeLists.txt
    SHA512 0d5173d7640e2b411dddfc67e1ee19c921817e58de36ea8325430ee79408edc0a23e17159e22dc4a05f169596ee866effa69e7cd0000b08f47bd090d5003ba1c
    HEAD_REF master
    PATCHES
        "${SOURCE_PATH}/cmake/cpm/patches/icm/regex-build-error.diff"
)

vcpkg_find_acquire_program(GIT)

vcpkg_cmake_configure(
    SOURCE_PATH "${SOURCE_PATH}"
    OPTIONS
        -DSTDEXEC_BUILD_TESTS=OFF
        -DSTDEXEC_BUILD_EXAMPLES=OFF
        "-DFETCHCONTENT_SOURCE_DIR_RAPIDS-CMAKE=${SOURCE_PATH_RAPIDS}"
        "-DCPM_SOURCE_CACHE=${CURRENT_BUILDTREES_DIR}/cpm"
        "-DCPM_icm_SOURCE=${SOURCE_PATH_ICM}"
        "-DGIT_EXECUTABLE=${GIT}"
)

vcpkg_cmake_install()

vcpkg_cmake_config_fixup(CONFIG_PATH lib/cmake/stdexec)

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/lib")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE.txt")
