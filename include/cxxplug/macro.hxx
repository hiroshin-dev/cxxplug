///
/// Copyright (c) 2022 Hiroshi Nakashima
///
/// This software is released under the MIT License, see LICENSE.
///
/// @file
///
#ifndef CXXPLUG_MACRO_HXX_
#define CXXPLUG_MACRO_HXX_

#define CXXPLUG_ENTRY(variable) \
  static void _cxxplug_entry(cxxplug::Plugin&); \
  extern "C" void cxxplug_entry(void *plugin_ptr) { \
    _cxxplug_entry(*reinterpret_cast<cxxplug::Plugin*>(plugin_ptr)); \
  } \
  void _cxxplug_entry(cxxplug::Plugin &(variable))

#endif  // CXXPLUG_MACRO_HXX_
