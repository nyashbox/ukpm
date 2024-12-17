
// SPDX-License-Identifier: Apache-2.0
// Copyright (c) 2024 nyashbox and Contributors

#include "manifest/package_build.h"

// manifest filename
const std::string MANIFEST_NAME = "@PKGBUILD";

// json schema
const std::string JSON_SCHEMA = R"(
{
	"$schema":"http://json-schema.org/draft-07/schema#",
	"type":"object",
	"properties":{
		"syntax":{
			"type":"string",
			"enum":[
				"1"
			]
		},
		"source":{
			"type":"object",
			"properties":{
				"url":{
					"type":"string",
					"format":"uri"
				},
				"sha256":{
					"type":"string",
					"pattern":"^[a-fA-F0-9]{64}$"
				}
			},
			"required":[
				"url",
				"sha256"
			],
			"additionalProperties":false
		},
		"patches":{
			"type":"array",
			"items":{
				"type":"object",
				"properties":{
					"file":{
						"type":"string"
					},
					"description":{
						"type":"string"
					}
				},
				"required":[
					"file",
					"description"
				],
				"additionalProperties":false
			}
		}
	},
	"required":[
		"syntax",
		"source"
	],
	"additionalProperties":false
}
)";

namespace ukpm {
namespace manifest {

PackageBuild::PackageBuild(const std::string &file) { read(file); };
PackageBuild::PackageBuild(PackageArchive &archive) { read(archive); };

void PackageBuild::read(PackageArchive &archive) {
    _read(archive, MANIFEST_NAME);
};

void PackageBuild::validate(void) { _validate(JSON_SCHEMA); };

} // namespace manifest
} // namespace ukpm
