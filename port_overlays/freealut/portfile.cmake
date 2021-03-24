vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO vancegroup/freealut
    REF fc814e316c2bfa6e05b723b8cc9cb276da141aae
    HEAD_REF master
    SHA512 046990cc13822ca6eea0b8e412aa95a994b881429e0b15cefee379f08bd9636d4a4598292a8d46b30c3cd06814bfaeae3298e8ef4087a46eede344f3880e9fed
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
    DISABLE_PARALLEL_CONFIGURE
    OPTIONS -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
)

vcpkg_install_cmake()
#vcpkg_fixup_cmake_targets(CONFIG_PATH lib/cmake/freealut TARGET_PATH share/freealut)
vcpkg_fixup_pkgconfig()
vcpkg_copy_pdbs()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug/share
                     ${CURRENT_PACKAGES_DIR}/debug/include
 )

file(INSTALL ${SOURCE_PATH}/COPYING DESTINATION ${CURRENT_PACKAGES_DIR}/share/${PORT} RENAME copyright)
