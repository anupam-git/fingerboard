set(CPACK_GENERATOR "DEB")

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_DEPENDS
    "fprintd"
    "qml-module-qtquick-controls"
    "qml-module-qtquick-controls2"
    "qml-module-qtquick-layouts"
    "qml-module-qtgraphicaleffects"
)

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Anupam Basak")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fprintd based GUI for listing, enrolling, deleting and verifying fingerprints for Linux")
set(CPACK_PACKAGE_VENDOR "Anupam Basak")
set(CPACK_PACKAGE_CONTACT "Anupam Basak <anupam.basak27@gmail.com>")

set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.rst")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
set(CPACK_SOURCE_STRIP_FILES "")

include(CPack)

 
