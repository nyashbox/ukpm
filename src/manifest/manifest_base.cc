
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#include "manifest/manifest_base.h"

namespace ukpm {
namespace manifest {

void ManifestBase::read(const std::string &file) {
    std::ifstream fileStream(file);

    if (!fileStream)
        throw std::runtime_error("failed to open manifest file");

    try {
        _data = json::parse(fileStream);
    } catch (...) {
        throw;
    }
};

void ManifestBase::_validate(const std::string &schema) {
    auto jsonSchema = json::parse(schema);
    auto compiledSchema = jsoncons::jsonschema::make_json_schema(jsonSchema);

    try {
        compiledSchema.validate(_data);
    } catch (...) {
        throw;
    }
};

void ManifestBase::_read(PackageArchive &archive, const std::string &filename) {
    try {
        auto file = archive.read(filename);
        _data = json::parse(file);
    } catch (...) {
        throw;
    }
};

const json &ManifestBase::data(void) const { return _data; };

} // namespace manifest
} // namespace ukpm
