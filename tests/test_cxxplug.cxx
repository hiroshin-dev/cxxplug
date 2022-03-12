///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#include <string>

#include "gtest/gtest.h"

#include "cxxplug/cxxplug.hxx"
#include "cxxlog/cxxlog.hxx"

namespace {

std::string get_plugin_path() {
  return cxxplug::get_environment("PLUGIN_PATH");
}

}  // namespace

TEST(cxxplug, get_version) {
  const auto version = cxxplug::get_version();
  ASSERT_NE(version, nullptr);
  CXXLOG_I << version->major();
  CXXLOG_I << version->minor();
  CXXLOG_I << version->patch();
  CXXLOG_I << version->vcs_branch();
  CXXLOG_I << version->vcs_commit_hash();
  CXXLOG_I << version->vcs_commit_date();
}

TEST(Plugin, load) {
  const auto plugin_path = get_plugin_path();
  const auto plugin = cxxplug::Plugin::load(plugin_path);
  ASSERT_NE(plugin, nullptr);
  EXPECT_EQ(plugin->library_path(), plugin_path);
}

TEST(Plugin, load_error) {
  {
    const auto plugin = cxxplug::Plugin::load("non-existent");
    EXPECT_EQ(plugin, nullptr);
  }
  {
    const auto plugin = cxxplug::Plugin::load("");
    EXPECT_EQ(plugin, nullptr);
  }
}

TEST(Plugin, get_available_classes) {
  const auto plugin = cxxplug::Plugin::load(get_plugin_path());
  ASSERT_NE(plugin, nullptr);
  const auto class_names = plugin->get_available_classes<cxxplug::I_Version>();
  const std::vector<std::string> expected { "Version" };
  EXPECT_EQ(class_names, expected);
}

TEST(Plugin, create_instance) {
  const auto plugin = cxxplug::Plugin::load(get_plugin_path());
  ASSERT_NE(plugin, nullptr);
  const auto object = plugin->create_instance<cxxplug::I_Version>("Version");
  ASSERT_NE(object, nullptr);
  EXPECT_EQ(object->major(), 1);
  EXPECT_EQ(object->minor(), 2);
  EXPECT_EQ(object->patch(), 3);
  EXPECT_EQ(object->vcs_branch(), "branch");
  EXPECT_EQ(object->vcs_commit_hash(), "hash");
  EXPECT_EQ(object->vcs_commit_date(), "date");
}

TEST(Plugin, create_instance_error) {
  const auto plugin = cxxplug::Plugin::load(get_plugin_path());
  ASSERT_NE(plugin, nullptr);
  const auto object =
      plugin->create_instance<cxxplug::I_Version>("non-existent");
  EXPECT_EQ(object, nullptr);
}
