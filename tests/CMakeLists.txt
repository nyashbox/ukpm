
# SPDX-License-Identifier: Apache-2.0 
# Copyright (c) 2024 nyashbox and Contributors

# check if we should build
if(NOT UKPM_ENABLE_TESTS)
    return()
endif()

# test sources
set(UKPM_TEST_SOURCES
    core/archive.test.cc

    package/binary_package.test.cc
    package/source_package.test.cc
)

# setup test requirements
find_package(GTest REQUIRED)
include(GoogleTest)

# creating testrunner
add_executable(ukpm_testrunner ${UKPM_TEST_SOURCES})
target_link_libraries(ukpm_testrunner
    PUBLIC
        GTest::gtest
        GTest::gtest_main
        ukpm::ukpm
)

# discover tests
gtest_discover_tests(ukpm_testrunner
    WORKING_DIRECTORY
        ${CMAKE_CURRENT_LIST_DIR})
