#include <gtest/gtest.h>

#include "manifest/package_info.h"

using ukpm::manifest::PackageInfo;

TEST(PackageInfo, read) {
    PackageInfo pkginfo;

    PackageArchive archive("data/package/pkginfo.tar.zstd");
    EXPECT_NO_THROW(pkginfo.read(archive))
        << "Reading correct package info file from archive MUST NOT throw";

    EXPECT_NO_THROW(pkginfo.read("data/package/@PKGINFO"))
        << "Reading correct package info file MUST NOT throw";

    EXPECT_ANY_THROW(pkginfo.read("data/package/@PKGINFO-borked"))
        << "Reading corrupted package info file MUST throw";
}

TEST(PackageInfo, validate) {
    PackageInfo pkginfo;

    pkginfo.read("data/package/@PKGINFO");
    EXPECT_NO_THROW(pkginfo.validate())
        << "Validating correct package info file MUST NOT throw";

    pkginfo.read("data/package/@PKGINFO-missing");
    EXPECT_ANY_THROW(pkginfo.validate())
        << "Validating malformed package info file MUST throw";
}
