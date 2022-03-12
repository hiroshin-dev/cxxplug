#
# Copyright (c) 2022 Hiroshi Nakashima
#
# This software is released under the MIT License, see LICENSE.
#
add_library(test_plugin SHARED plugin.cxx)
target_link_libraries(test_plugin cxxplug::cxxplug)
target_compile_options(test_plugin PRIVATE ${WARNING_OPTIONS})
