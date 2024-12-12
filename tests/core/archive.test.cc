
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#include <gtest/gtest.h>

#include "core/archive.h"

using ukpm::core::ArchiveFile;
using ukpm::core::PackageArchive;

TEST(Archive, open) {
    EXPECT_ANY_THROW(PackageArchive("data/core/missing.tar.zstd"))
        << "Trying to open archive with incorrect path MUST throw exception";

    EXPECT_NO_THROW(PackageArchive("data/core/archive.tar.zstd"))
        << "Opening archive with correct path MUST NOT throw exception";
}

TEST(Archive, read) {
    PackageArchive archive;
    ArchiveFile actualFile;
    ArchiveFile expectedFile{'t', 'e', 's', 't', 't', 'e', 's',
                             't', 't', 'e', 's', 't', '\n'};

    EXPECT_ANY_THROW(archive.read("data.txt"))
        << "Reading file from unopened archive MUST throw exception";

    EXPECT_NO_THROW(archive.open("data/core/archive.tar.zstd"))
        << "[SANITY CHECK] Archive opening MUST NOT fail before reading file";

    EXPECT_NO_THROW((actualFile = archive.read("data.txt")))
        << "Reading file that is in archive MUST NOT throw exception";

    // check if data was read correctly
    EXPECT_EQ(actualFile, expectedFile);
}

TEST(Archive, close) {
    EXPECT_ANY_THROW(PackageArchive().close())
        << "Closing archive that WASN'T previously opened MUST throw exception";

    EXPECT_NO_THROW(PackageArchive("data/core/archive.tar.zstd").close())
        << "Closing opened archive MUST NOT throw exception";
}
