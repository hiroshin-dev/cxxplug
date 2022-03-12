#
# Copyright (c) 2022 Hiroshi Nakashima
#
# This software is released under the MIT License, see LICENSE.
#
include(TestFunction)

add_subdirectory(plugin)

add_plugin_test(test_cxxplug
    SOURCES test_cxxplug.cxx
    PROPERTIES ENVIRONMENT
        "PLUGIN_PATH=$<TARGET_FILE:test_plugin>"
)

add_plugin_test(test_utils
    SOURCES test_utils.cxx
    PROPERTIES ENVIRONMENT
        "TEST_ENVIRONMENT=test-environment"
)
