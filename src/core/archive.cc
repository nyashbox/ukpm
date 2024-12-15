
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#include "core/archive.h"

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

void PackageArchive::open(const std::filesystem::path &path) {
    // mark archive as 'open'
    _isOpen = true;
    auto res = archive_read_open_filename(_archive, path.c_str(), BLOCK_SIZE);

    if (res != ARCHIVE_OK)
        throw std::runtime_error(archive_error_string(_archive));
}

ArchiveFile PackageArchive::read(const std::string &file) {

    // check if archive is open
    if (not _isOpen)
        throw std::runtime_error("Archive should be open before using");

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
    throw std::runtime_error("file not found!");
}

void PackageArchive::close(void) {
    // check if archive is open
    if (not _isOpen)
        throw std::runtime_error(
            "can't close archive that wasn't opened previously");

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
