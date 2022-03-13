///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#include "cxxplug/cxxplug.hxx"

namespace {

class Version : public cxxplug::I_Version {
  int32_t major() const final { return 1; }
  int32_t minor() const final { return 2; }
  int32_t patch() const final { return 3; }
  std::string vcs_branch() const final { return "branch"; }
  std::string vcs_commit_hash() const final { return "hash"; }
  std::string vcs_commit_date() const final { return "date"; }
};

}  // namespace

CXXPLUG_ENTRY(plugin) {
  plugin.register_class<cxxplug::I_Version, Version>("Version");
}
