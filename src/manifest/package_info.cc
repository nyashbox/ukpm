#include "manifest/package_info.h"

#include <jsoncons_ext/jsonschema/json_schema.hpp>

#include <fstream>
#include <jsoncons_ext/jsonschema/json_schema_factory.hpp>

// manifest filename
const std::string MANIFEST_NAME = "@PKGINFO";

// json schema
const std::string JSON_SCHEMA = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "type": "object",
    "required": ["syntax", "manifest", "kernel"],
    "properties": {
        "syntax": {
            "type": "string",
			"enum": ["1"]
        },
        "manifest": {
            "type": "object",
            "required": ["package-type", "maintainers", "homepage"],
            "properties": {
                "package-type": {
                    "type": "string",
                    "enum": ["source", "binary"]
                },
                "maintainers": {
                    "type": "array",
                    "items": {
                        "type": "object",
                        "required": ["maintainer", "mail"],
                        "properties": {
                            "maintainer": { "type": "string" },
                            "mail": {
                                "type": "string",
								"format": "email"
                            }
                        }
                    }
                },
                "homepage": {
                    "type": "string",
					"format": "uri"
                }
            }
        },
        "kernel": {
            "type": "object",
            "required": ["platform", "flavor", "version"],
            "properties": {
                "platform": {
                    "type": "string",
                    "enum": ["linux"]
                },
                "flavor": {
                    "type": "string"
                },
                "version": {
                    "type": "string"
                }
            }
        }
    },
    "additionalProperties": false
}
)";

namespace ukpm {
namespace manifest {

PackageInfo::PackageInfo(const std::filesystem::path &file) { read(file); }
PackageInfo::PackageInfo(PackageArchive &archive) { read(archive); };

void PackageInfo::read(const std::filesystem::path &file) {
    std::ifstream fileStream(file);

    if (!fileStream)
        throw std::runtime_error("failed to open package info file");

    try {
        _data = json::parse(fileStream);
    } catch (...) {
        throw;
    }
};

void PackageInfo::read(PackageArchive &archive) {
    auto file = archive.read(MANIFEST_NAME);

    try {
        _data = json::parse(file);
    } catch (...) {
        throw;
    }
};

void PackageInfo::validate(void) {
    auto schema = json::parse(JSON_SCHEMA);
    auto compiledSchema =
        jsoncons::jsonschema::make_json_schema(std::move(schema));

    try {
        compiledSchema.validate(_data);
    } catch (...) {
        throw;
    }
};

} // namespace manifest
} // namespace ukpm
