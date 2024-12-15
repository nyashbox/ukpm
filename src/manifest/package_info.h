#ifndef UKPM_MANIFEST_PACKAGE_INFO_H_
#define UKPM_MANIFEST_PACKAGE_INFO_H_

#pragma once

#include "core/archive.h"
#include "manifest/manifest_base.h"

#include <filesystem>

using ukpm::core::PackageArchive;

namespace ukpm {
namespace manifest {

class PackageInfo final : public ManifestBase {
  public:
    using ManifestBase::read;

    PackageInfo() = default;
    PackageInfo(const std::filesystem::path &file);
    PackageInfo(PackageArchive &archive);

    virtual void read(PackageArchive &archive) override;

    virtual void validate(void) override;

  protected:
  private:
};

} // namespace manifest
} // namespace ukpm

#endif // UKPM_MANIFEST_PACKAGE_INFO_H_
