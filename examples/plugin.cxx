///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#include "cxxplug/cxxplug.hxx"

#include "plugin_impl.hxx"

CXXPLUG_ENTRY(plug) {
  plug.register_class<cxxplug::I_Version, Version>("Version")
      .register_class<example::I_Example, example::Foo>("example::Foo")
      .register_class<example::I_Example, example::Bar>("example::Bar");
}
