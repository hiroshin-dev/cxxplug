///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#ifndef CXXPLUG_EXAMPLES_PLUGIN_IMPL_HXX
#define CXXPLUG_EXAMPLES_PLUGIN_IMPL_HXX

#include "cxxplug/cxxplug.hxx"

#include "plugin.hxx"

class Version : public cxxplug::I_Version {
  int32_t major() const final { return 1; }
  int32_t minor() const final { return 2; }
  int32_t patch() const final { return 3; }
  std::string vcs_branch() const final { return "branch"; }
  std::string vcs_commit_hash() const final { return "hash"; }
  std::string vcs_commit_date() const final { return "date"; }
};

namespace example {

class Foo : public I_Example {
 public:
  Foo();
  explicit Foo(int32_t serial, const std::string &name);
  int32_t serial() const final;
  std::string name() const final;

 private:
  int32_t serial_;
  std::string name_;
};

class Bar : public Foo {
 public:
  Bar();
};

}  // namespace example

#endif  // CXXPLUG_EXAMPLES_PLUGIN_IMPL_HXX
