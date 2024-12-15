
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#include "manifest/package_info.h"
#include "manifest/manifest_base.h"

#include <fstream>

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

void PackageInfo::read(PackageArchive &archive) {
    _read(archive, MANIFEST_NAME);
};

void PackageInfo::validate(void) { _validate(JSON_SCHEMA); };

} // namespace manifest
} // namespace ukpm
