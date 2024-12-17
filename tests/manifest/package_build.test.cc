
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#include <gtest/gtest.h>

#include "manifest/package_build.h"

using ukpm::manifest::PackageBuild;

const auto MANIFEST_GOOD = "data/manifest/package_build/good";
const auto MANIFEST_BORKED = "data/manifest/package_build/borked";
const auto MANIFEST_MISSING = "data/manifest/package_build/missing";

TEST(PackageBuild, read) {
    PackageBuild pkgbuild;

    EXPECT_NO_THROW(pkgbuild.read(MANIFEST_GOOD))
        << "Reading correct @PKGBUILD file MUST NOT throw";

    EXPECT_ANY_THROW(pkgbuild.read(MANIFEST_BORKED))
        << "Reading corrupted @PKGBUILD file MUST throw";
}

TEST(PackageBuild, validate) {
    PackageBuild pkgbuild;

    pkgbuild.read(MANIFEST_GOOD);
    EXPECT_NO_THROW(pkgbuild.validate())
        << "Validating correct @PKGBUILD file MUST NOT throw";

    pkgbuild.read(MANIFEST_MISSING);
    EXPECT_ANY_THROW(pkgbuild.validate())
        << "Validating malformed @PKGBUILD file MUST throw";
}
