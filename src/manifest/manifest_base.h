#ifndef UKPM_MANIFEST_MANIFEST_BASE_H_
#define UKPM_MANIFEST_MANIFEST_BASE_H_

#pragma once

namespace ukpm {
namespace manifest {

class ManifestBase {
  public:
    virtual void validate(void) = 0;

  protected:
  private:
};

} // namespace manifest
} // namespace ukpm

#endif // UKPM_MANIFEST_MANIFEST_BASE_H_
