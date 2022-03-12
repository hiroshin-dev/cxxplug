///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
/// @file
///
#ifndef CXXPLUG_VERSION_VERSION_HXX_
#define CXXPLUG_VERSION_VERSION_HXX_

#include "cxxplug/version.hxx"

namespace cxxplug {

class Version : public I_Version {
 public:
  int32_t major() const final;
  int32_t minor() const final;
  int32_t patch() const final;
  std::string vcs_branch() const final;
  std::string vcs_commit_hash() const final;
  std::string vcs_commit_date() const final;
};

}  // namespace cxxplug

#endif  // CXXPLUG_VERSION_VERSION_HXX_
