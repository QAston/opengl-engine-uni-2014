vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO cesarizu/freealut
    REF e7dc5c297e8223a85f9b848c0ff56970db6344b6
    PATCHES cmake_builds.patch unix_headers.patch 
    HEAD_REF master
    SHA512 1e4e347de70094d0288c9a11ffedbbd3246d99403c2199c692c1bdd5f8ddfd31354dc597c137ce99ab59acc50657007e47153735e189a13152fdc2cef434c09e
)

string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "static" ALUT_BUILD_STATIC)
string(COMPARE EQUAL "${VCPKG_LIBRARY_LINKAGE}" "dynamic" ALUT_BUILD_DYNAMIC)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    DISABLE_PARALLEL_CONFIGURE
    OPTIONS -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF -DBUILD_STATIC=${ALUT_BUILD_STATIC} -DBUILD_DYNAMIC=${ALUT_BUILD_DYNAMIC}
)

vcpkg_install_cmake()
vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/freealut TARGET_PATH share/freealut)
vcpkg_fixup_pkgconfig()
vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/share"
                    "${CURRENT_PACKAGES_DIR}/debug/include"
 )

if(VCPKG_LIBRARY_LINKAGE STREQUAL "static")
    file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/bin" "${CURRENT_PACKAGES_DIR}/debug/bin")
endif()

file(INSTALL ${SOURCE_PATH}/COPYING DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
