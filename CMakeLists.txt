
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2024 nyashbox and Contributors

cmake_minimum_required(VERSION 3.15.0)

# project description
project(ukpm
        DESCRIPTION "Kernel package manager for Unix-like operating systems"
        VERSION 0.1.0
        LANGUAGES CXX)

list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# includes
include(CTest)
include(Sanitizers)

# c++ options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# build options
option(UKPM_ENABLE_TESTS "Build application tests" ON)
option(UKPM_ENABLE_ASAN  "Build with address sanitizer" OFF)

# subdirectories
add_subdirectory(src)
add_subdirectory(tests)
