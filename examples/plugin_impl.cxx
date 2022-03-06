///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#include "plugin_impl.hxx"

namespace example {

Foo::Foo()
    : serial_(1), name_("foo") {
}

Foo::Foo(int32_t serial, const std::string &name)
    : serial_(serial), name_(name) {
}

int32_t Foo::serial() const {
  return serial_;
}

std::string Foo::name() const {
  return name_;
}

Bar::Bar()
    : Foo(5, "bar") {
}

}  // namespace example
