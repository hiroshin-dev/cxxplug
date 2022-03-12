///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#include "gtest/gtest.h"

#include "cxxplug/cxxplug.hxx"

TEST(utils, get_environment) {
  {
    const auto value = cxxplug::get_environment("TEST_ENVIRONMENT");
    EXPECT_EQ(value, "test-environment");
  }
  {
    const auto value = cxxplug::get_environment("non-existent", "error");
    EXPECT_EQ(value, "error");
  }
}

TEST(utils, get_library_name) {
  const auto library_name = cxxplug::get_library_name("test");
#ifdef _WIN32
  const auto expect = "test.dll";
#else
  const auto expect = "libtest.so";
#endif  // _WIN32
  EXPECT_EQ(library_name, expect);
}
