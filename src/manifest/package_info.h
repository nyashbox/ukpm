#ifndef UKPM_MANIFEST_PACKAGE_INFO_H_
#define UKPM_MANIFEST_PACKAGE_INFO_H_

#pragma once

#include "core/archive.h"
#include "manifest/manifest_base.h"

#include <jsoncons/json.hpp>

#include <filesystem>

using ukpm::core::PackageArchive;

using jsoncons::json;

namespace ukpm {
namespace manifest {

class PackageInfo final : public ManifestBase {
  public:
    PackageInfo() = default;
    PackageInfo(const std::filesystem::path &file);
    PackageInfo(PackageArchive &archive);

    void read(const std::filesystem::path &file);
    void read(PackageArchive &archive);

    virtual void validate(void) override;

  protected:
  private:
    json _data;
};

} // namespace manifest
} // namespace ukpm

#endif // UKPM_MANIFEST_PACKAGE_INFO_H_
