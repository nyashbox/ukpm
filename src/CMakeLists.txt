
# SPDX-License-Identifier: Apache-2.0 
# Copyright (c) 2024 nyashbox and Contributors

# application sources
set(UKPM_SOURCES
    core/archive.cc

    package/binary_package.cc
    package/source_package.cc
)

find_package(LibArchive REQUIRED)
find_package(nlohmann_json_schema_validator REQUIRED)

add_library(libukpm OBJECT ${UKPM_SOURCES})
add_library(ukpm::ukpm ALIAS libukpm)

target_link_libraries(libukpm 
    PUBLIC
        LibArchive::LibArchive 
        nlohmann_json::nlohmann_json
        nlohmann_json_schema_validator
)

target_include_directories(libukpm
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
)

add_executable(ukpm ukpm.cc)
target_link_libraries(ukpm PUBLIC ukpm::ukpm)
