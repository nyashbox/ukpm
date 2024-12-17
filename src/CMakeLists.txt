
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2024 nyashbox and Contributors

# application sources
set(UKPM_SOURCES
    core/archive.cc

    manifest/package_info.cc
    manifest/package_build.cc
    manifest/manifest_base.cc

    package/binary_package.cc
    package/source_package.cc
)

find_package(LibArchive REQUIRED)
find_package(jsoncons REQUIRED)

add_library(libukpm OBJECT ${UKPM_SOURCES})
add_library(ukpm::ukpm ALIAS libukpm)

target_link_libraries(libukpm
    PUBLIC
        LibArchive::LibArchive
        jsoncons
)

target_include_directories(libukpm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

target_precompile_headers(libukpm
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/pch.h)

if(UKPM_ENABLE_ASAN)
    ukpm_target_enable_asan(libukpm)
endif()

add_executable(ukpm ukpm.cc)
target_link_libraries(ukpm PUBLIC ukpm::ukpm)
