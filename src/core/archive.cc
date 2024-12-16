
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#include "core/archive.h"
#include "core/exception.h"

#include <archive.h>
#include <archive_entry.h>

const size_t BLOCK_SIZE = 10240;

namespace ukpm {
namespace core {

PackageArchive::PackageArchive() {
    _archive = archive_read_new();

    archive_read_support_format_tar(_archive);
    archive_read_support_filter_zstd(_archive);
}

PackageArchive::PackageArchive(const std::filesystem::path &path)
    : PackageArchive() {
    open(path);
}

const struct archive &PackageArchive::archive() const { return *_archive; };

void PackageArchive::open(const std::filesystem::path &path) {
    // mark archive as 'open'
    _isOpen = true;
    auto res = archive_read_open_filename(_archive, path.c_str(), BLOCK_SIZE);

    if (res != ARCHIVE_OK)
        throw ukpm::ArchiveException("Failed to open archive: ",
                                     archive_error_string(_archive));
}

ArchiveFile PackageArchive::read(const std::string &file) {

    // check if archive is open
    if (not _isOpen)
        throw ukpm::ArchiveException("Failed to read from archive: archive "
                                     "should be open before reading!");

    struct archive_entry *entry;
    ArchiveFile archiveFile;

    while (archive_read_next_header(_archive, &entry) == ARCHIVE_OK) {
        const std::string filename = archive_entry_pathname(entry);

        if (filename == file) {
            // allocate enough memory to hold file
            archiveFile.resize(archive_entry_size(entry));

            // read data into vector
            archive_read_data(_archive, archiveFile.data(), archiveFile.size());
            archive_read_data_skip(_archive);

            return archiveFile;
        }

        // skip reading unrequired files
        archive_read_data_skip(_archive);
    }

    // throw exception if file is not in archive
    throw ukpm::ArchiveException(
        "Failed to read from archive: file not found!");
}

void PackageArchive::close(void) {
    // check if archive is open
    if (not _isOpen)
        throw ukpm::ArchiveException(
            "Failed to close archive: archive should be open before closing!");

    // close archive and deallocate memory
    archive_read_close(_archive);
    archive_read_free(_archive);

    // set private members to initial state
    _archive = nullptr;
    _isOpen = false;
};

PackageArchive::~PackageArchive() {
    // don't close unopened archive
    if (_archive != nullptr) {
        archive_read_free(_archive);
    }
};

} // namespace core
} // namespace ukpm
