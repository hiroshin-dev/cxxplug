///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#ifndef CXXPLUG_EXAMPLES_PLUGIN_HXX
#define CXXPLUG_EXAMPLES_PLUGIN_HXX

#include <stdint.h>
#include <string>

namespace example {

class I_Example {
 public:
  virtual ~I_Example() = default;
  virtual int32_t serial() const = 0;
  virtual std::string name() const = 0;
};

}  // namespace example

#endif  // CXXPLUG_EXAMPLES_PLUGIN_HXX
