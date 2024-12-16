# Abstract

**@PKGINFO** file stores kernel package metadata.

---
# Example
Example syntax for **@PKGINFO** can be seen below.
```json
{
	"syntax": "1",

	"manifest": {
		"package-type": "source",
		"maintainers": [{
			"maintainer": "maintainer",
			"mail": "maintainer@localhost"
		}],
		"homepage": "https://kernel.org"
	},

	"kernel": {
		"platform": "linux",
		"flavor": "vanilla",
		"version": "6.12.4"
    }
}
```
---
# Syntax reference

This section contains syntax reference for **@PKGINFO** file.

## 1. syntax
**Required:** yes
**Type:** string
**Checked:** yes
**Possible Values:** { 1 }

## 2. manifest
**Required:** yes
**Type:** object
**Checked:** partially

## 2.1 manifest.package-type
**Required:** yes
**Type:** string
**Checked:** yes
**Possible values:** { "source" | "binary" }

## 2.2 manifest.maintainers
**Required:** yes
**Type:** array
**Checked:** no

## 2.2.1 manifest.maintainers.maintainer
**Required:** yes
**Type:** string
**Checked:** no

## 2.2.2 manifest.maintainers.mail
**Required:** yes
**Type:** string
**Checked:** no

## 2.3 homepage
**Required:** yes
**Type:** string
**Checked:** no
Link to the upstream (or project page)
Example: https://kernel.org

## 3. kernel
**Required:** yes
**Type:** object
**Checked:** partially

## 3.1 kernel.platform
**Required:** yes
**Type:**: string
**Checked:** yes
**Possible values:** { "linux" }

## 3.2. kernel.flavor
**Required:** yes
**Type:**: string
**Checked:** no

## 3.3 kernel.version
**Required:** yes
**Type:** string
**Checked:** no
Can have any format
