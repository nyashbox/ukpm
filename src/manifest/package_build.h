
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#ifndef UKPM_MANIFEST_PACKAGE_BUILD_H_
#define UKPM_MANIFEST_PACKAGE_BUILD_H_

#pragma once

#include "manifest/manifest_base.h"

namespace ukpm {
namespace manifest {

class PackageBuild final : public ManifestBase {
  public:
    using ManifestBase::read;

    PackageBuild() = default;
    PackageBuild(const std::string &file);
    PackageBuild(PackageArchive &archive);

    void read(PackageArchive &archive) override;

    void validate(void) override;

  protected:
  private:
};

} // namespace manifest
} // namespace ukpm

#endif // UKPM_MANIFEST_PACKAGE_BUILD_H_
