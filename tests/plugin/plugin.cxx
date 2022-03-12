///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
#include "cxxplug/cxxplug.hxx"

#include "plugin_impl.hxx"

extern "C" void plugin_entry(void *plugin_ptr) {
  auto &plugin = cxxplug::plugin_cast(plugin_ptr);
  plugin.register_class<cxxplug::I_Version, Version>("Version");
}
