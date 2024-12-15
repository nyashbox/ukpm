#ifndef UKPM_MANIFEST_MANIFEST_BASE_H_
#define UKPM_MANIFEST_MANIFEST_BASE_H_

#pragma once

#include "core/archive.h"

#include <jsoncons/json.hpp>

#include <string>

using ukpm::core::PackageArchive;

using jsoncons::json;

namespace ukpm {
namespace manifest {

class ManifestBase {
  public:
    [[nodiscard]]
    const json &data(void) const;

    virtual void read(const std::string &file);
    virtual void read(PackageArchive &archive) = 0;

    virtual void validate(void) = 0;

  protected:
    void _read(PackageArchive &archive, const std::string &filename);
    void _validate(const std::string &schema);

  private:
    json _data;
};

} // namespace manifest
} // namespace ukpm

#endif // UKPM_MANIFEST_MANIFEST_BASE_H_
