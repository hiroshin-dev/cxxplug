#
# Copyright (c) 2022 Hiroshi Nakashima
#
# This software is released under the MIT License, see LICENSE.
#
include(function/add_plugin_test)

add_plugin_test(test_plugin
    SOURCES test_plugin.cxx
    PROPERTIES ENVIRONMENT
        "PLUGIN_PATH=$<TARGET_FILE:example_plugin>"
)

add_plugin_test(test_utils
    SOURCES test_utils.cxx
    PROPERTIES ENVIRONMENT
        "TEST_ENVIRONMENT=test-environment"
)
