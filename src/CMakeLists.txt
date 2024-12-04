
# SPDX-License-Identifier: Apache-2.0 
# Copyright (c) 2024 nyashbox and Contributors

# application sources
set(UKPM_SOURCES
    core/stub.cc
)

add_library(libukpm OBJECT ${UKPM_SOURCES})
add_library(ukpm::ukpm ALIAS libukpm)

add_executable(ukpm ukpm.cc $<TARGET_OBJECTS:ukpm::ukpm>)
