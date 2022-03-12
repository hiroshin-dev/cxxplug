///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
/// @file
///
#ifndef CXXPLUG_UTILS_HXX_
#define CXXPLUG_UTILS_HXX_

#include <string>

namespace cxxplug {

std::string get_environment(
    const std::string &name, const std::string &default_value = std::string());

std::string get_library_name(const std::string &plugin_name);

}  // namespace cxxplug

#endif  // CXXPLUG_UTILS_HXX_
