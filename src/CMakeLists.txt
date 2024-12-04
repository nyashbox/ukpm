
# SPDX-License-Identifier: Apache-2.0 
# Copyright (c) 2024 nyashbox and Contributors

# application sources
set(UKPM_SOURCES
    package/binary_package.cc
    package/source_package.cc
)

add_library(libukpm OBJECT ${UKPM_SOURCES})
add_library(ukpm::ukpm ALIAS libukpm)

target_include_directories(libukpm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

add_executable(ukpm ukpm.cc $<TARGET_OBJECTS:ukpm::ukpm>)
