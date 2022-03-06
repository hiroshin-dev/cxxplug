///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#include "cxxplug/utils.hxx"

#include <stdlib.h>
#include <vector>

namespace cxxplug {

std::string get_environment(
    const std::string &name, const std::string &default_value) {
#ifdef _WIN32
  size_t required_size = 0;
  getenv_s(&required_size, nullptr, 0, name.c_str());
  if (required_size == 0) {
    return default_value;
  }
  std::vector<char> buffer(required_size);
  getenv_s(&required_size, buffer.data(), buffer.size(), name.c_str());
  return buffer.data();
#else
  const auto value = getenv(name.c_str());
  return (value != nullptr) ? value : default_value;
#endif  // _WIN32
}

}  // namespace cxxplug
