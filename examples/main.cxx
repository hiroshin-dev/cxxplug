///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#include <string>

#include "cxxplug/cxxplug.hxx"
#include "cxxlog/cxxlog.hxx"

#include "plugin.hxx"

namespace {

std::string get_current_dir(const std::string &executable_path) {
  return executable_path.substr(0, executable_path.find_last_of("/\\") + 1);
}

}  // namespace

int32_t main(int32_t, char **argv) {
  const auto current_dir = get_current_dir(argv[0]);
  const auto library_name = cxxplug::get_library_name("example_plugin");

  auto plugin = cxxplug::Plugin::load(current_dir + library_name);

  if (plugin != nullptr) {
    auto version = plugin->create_instance<cxxplug::I_Version>("Version");
    if (version != nullptr) {
      CXXLOG_I << "[Version] "
          << version->major() << '.'
          << version->minor() << '.'
          << version->patch() << " / "
          << version->vcs_branch() << " / "
          << version->vcs_commit_hash() << " / "
          << version->vcs_commit_date();
    }

    for (const auto &class_name :
        plugin->get_available_classes<example::I_Example>()) {
      auto object = plugin->create_instance<example::I_Example>(class_name);
      if (object != nullptr) {
        CXXLOG_I << "[" << class_name << "] "
            << object->serial() << ", " << object->name();
      }
    }
  }

  return 0;
}
