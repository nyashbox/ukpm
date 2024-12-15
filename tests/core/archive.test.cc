
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#include <gtest/gtest.h>

#include "core/archive.h"

using ukpm::core::ArchiveFile;
using ukpm::core::PackageArchive;

// test data
const auto ARCHIVE_GOOD = "data/core/archive/archive";
const auto ARCHIVE_MISSING = "data/core/archive/missing";

const auto TARGET_FILE = "data.txt";

TEST(Archive, open) {
    EXPECT_ANY_THROW(PackageArchive{ARCHIVE_MISSING})
        << "Trying to open archive with incorrect path MUST throw exception";

    EXPECT_NO_THROW(PackageArchive{ARCHIVE_GOOD})
        << "Opening archive with correct path MUST NOT throw exception";
}

TEST(Archive, read) {
    PackageArchive archive;
    ArchiveFile actualFile;
    const ArchiveFile expectedFile{'t', 'e', 's', 't', 't', 'e', 's',
                                   't', 't', 'e', 's', 't', '\n'};

    EXPECT_ANY_THROW(archive.read(TARGET_FILE))
        << "Reading file from unopened archive MUST throw exception";

    EXPECT_NO_THROW(archive.open(ARCHIVE_GOOD))
        << "[SANITY CHECK] Archive opening MUST NOT fail before reading file";

    EXPECT_NO_THROW((actualFile = archive.read(TARGET_FILE)))
        << "Reading file that is in archive MUST NOT throw exception";

    // check if data was read correctly
    EXPECT_EQ(actualFile, expectedFile);
}

TEST(Archive, close) {
    EXPECT_ANY_THROW(PackageArchive().close())
        << "Closing archive that WASN'T previously opened MUST throw exception";

    EXPECT_NO_THROW(PackageArchive(ARCHIVE_GOOD).close())
        << "Closing opened archive MUST NOT throw exception";
}
