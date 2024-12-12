
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#ifndef UKPM_CORE_ARCHIVE_H_
#define UKPM_CORE_ARCHIVE_H_

#pragma once

#include <archive.h>

#include <filesystem>

namespace ukpm {
namespace core {

using ArchiveFile = std::vector<unsigned char>;

class PackageArchive {
  public:
    PackageArchive();
    PackageArchive(const std::filesystem::path &path);

    ~PackageArchive();

    void open(const std::filesystem::path &path);
    void close();

    ArchiveFile read(const std::string &filename);

  protected:
  private:
    struct archive *_archive{nullptr};
    bool _isOpen{false};
};

} // namespace core
} // namespace ukpm

#endif // UKPM_CORE_ARCHIVE_H_
