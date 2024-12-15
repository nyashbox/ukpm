
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#include <gtest/gtest.h>

#include "manifest/package_info.h"

using ukpm::manifest::PackageInfo;

// test files
const auto ARCHIVE_GOOD = "data/manifest/package_info/archive";
const auto MANIFEST_GOOD = "data/manifest/package_info/good";
const auto MANIFEST_BORKED = "data/manifest/package_info/borked";
const auto MANIFEST_MISSING = "data/manifest/package_info/missing";

TEST(PackageInfo, read) {
    PackageInfo pkginfo;

    PackageArchive archive(ARCHIVE_GOOD);
    EXPECT_NO_THROW(pkginfo.read(archive))
        << "Reading correct package info file from archive MUST NOT throw";

    EXPECT_NO_THROW(pkginfo.read(MANIFEST_GOOD))
        << "Reading correct package info file MUST NOT throw";

    EXPECT_ANY_THROW(pkginfo.read(MANIFEST_BORKED))
        << "Reading corrupted package info file MUST throw";
}

TEST(PackageInfo, validate) {
    PackageInfo pkginfo;

    pkginfo.read(MANIFEST_GOOD);
    EXPECT_NO_THROW(pkginfo.validate())
        << "Validating correct package info file MUST NOT throw";

    pkginfo.read(MANIFEST_MISSING);
    EXPECT_ANY_THROW(pkginfo.validate())
        << "Validating malformed package info file MUST throw";
}
