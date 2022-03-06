///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
/// @file
///
#ifndef CXXPLUG_VERSION_HXX_
#define CXXPLUG_VERSION_HXX_

#include <stdint.h>
#include <string>

namespace cxxplug {

class I_Version {
 public:
  virtual ~I_Version() = default;
  virtual int32_t major() const = 0;
  virtual int32_t minor() const = 0;
  virtual int32_t patch() const = 0;
  virtual std::string vcs_branch() const = 0;
  virtual std::string vcs_commit_hash() const = 0;
  virtual std::string vcs_commit_date() const = 0;
};

}  // namespace cxxplug

#endif  // CXXPLUG_VERSION_HXX_
