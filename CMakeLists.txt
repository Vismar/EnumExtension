cmake_minimum_required(VERSION 3.14)
include(ExternalProject)


########################################################################################################################
# Install dependencies
set(EXTERNAL_INSTALL_DIR ../External)
#-----------------------------------------------------------------------------------------------------------------------
## Google Test
### Get gtest library
ExternalProject_Add(GoogleTest
                    GIT_REPOSITORY  https://github.com/google/googletest
                    SOURCE_DIR      "${EXTERNAL_INSTALL_DIR}/GoogleTest/src"
                    BINARY_DIR      "${EXTERNAL_INSTALL_DIR}/GoogleTest/build"
                    STAMP_DIR       "${EXTERNAL_INSTALL_DIR}/GoogleTest/stamp"
                    TMP_DIR         "${EXTERNAL_INSTALL_DIR}/GoogleTest/tmp"
                    GIT_TAG         release-1.8.1
                    # Install step is not required, so turn it off
                    UPDATE_COMMAND  ""
                    INSTALL_COMMAND "")
### Include gtest dependencies
include_directories(./External/GoogleTest/src/googletest/include)
### Gtest libs
set(GTEST_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/External/GoogleTest/build/googlemock")
#### G-Test
add_library(G-Test STATIC IMPORTED)
set_target_properties(G-Test PROPERTIES
        IMPORTED_LOCATION "${GTEST_LIB_PATH}/gtest/libgtest.a")
#### G-Test_main
add_library(G-Test_main STATIC IMPORTED)
set_target_properties(G-Test_main PROPERTIES
        IMPORTED_LOCATION "${GTEST_LIB_PATH}/gtest/libgtest_main.a")


########################################################################################################################
# C++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)


########################################################################################################################
# Project settings
project(EnumExtension)
include_directories(Include)


########################################################################################################################
# Tests
enable_testing ()
add_subdirectory(Tests)
########################################################################################################################