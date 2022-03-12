#
# Copyright (c) 2022 Hiroshi Nakashima
#
# This software is released under the MIT License, see LICENSE.
#
add_executable(cxxplug_example main.cxx)
target_link_libraries(cxxplug_example cxxplug::cxxplug cxxlog::cxxlog)
target_compile_definitions(cxxplug_example PRIVATE CXXLOG_LEVEL=cxxlog::debug)
target_compile_options(cxxplug_example PRIVATE ${WARNING_OPTIONS})

add_library(example_plugin SHARED plugin.cxx plugin_impl.cxx)
target_link_libraries(example_plugin cxxplug::cxxplug)
target_compile_options(example_plugin PRIVATE ${WARNING_OPTIONS})
