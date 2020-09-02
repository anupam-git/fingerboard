cmake_minimum_required(VERSION 3.0)

set(FINGERBOARD_VERSION 0.1.0)

project(fingerboard VERSION ${FINGERBOARD_VERSION})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(ECM 1.7.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${ECM_MODULE_PATH})

find_package(
    Qt5
        REQUIRED
        NO_MODULE

    COMPONENTS
        Core
        Qml
        Quick
        DBus
        QuickControls2
)

include(ECMSetupVersion)
include(FeatureSummary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ecm_setup_version(
  ${FINGERBOARD_VERSION}

  VARIABLE_PREFIX   FINGERBOARD
  VERSION_HEADER    "${CMAKE_CURRENT_BINARY_DIR}/fingerboard_version.h"
)

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

include(cpack.cmake)
