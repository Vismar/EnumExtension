cmake_minimum_required(VERSION 3.9)
project(UtilityTest)

#######################################################################################################################
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Test/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/Test/")

#######################################################################################################################
# Build executable
add_executable(Tests
        ValueAsStringTests.cpp
)

## Link libraries
target_link_libraries(Tests G-Test G-Test_main pthread)

## Prefix
set_target_properties(Tests PROPERTIES PREFIX "")


#######################################################################################################################
# Tests
add_test(NAME Tests COMMAND Tests)

#######################################################################################################################