#
# Copyright (c) 2022 Hiroshi Nakashima
#
# This software is released under the MIT License, see LICENSE.
#
find_package(GTest QUIET)

if(GTest_FOUND)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.20)
        set(GTEST_LIBRARIES GTest::gtest GTest::gtest_main)
    else()
        set(GTEST_LIBRARIES GTest::GTest GTest::Main)
    endif()
else()
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    set(GTEST_LIBRARIES gtest gtest_main)
endif()

include(GoogleTest)

function(add_plugin_test TEST_NAME)
    cmake_parse_arguments(TEST "" "" "SOURCES;LIBRARIES;PROPERTIES" ${ARGN})
    cmake_parse_arguments(TEST "" "" "ENVIRONMENT" ${TEST_PROPERTIES})

    add_executable(${TEST_NAME} ${TEST_SOURCES})
    target_link_libraries(${TEST_NAME}
        ${GTEST_LIBRARIES} ${TEST_LIBRARIES} cxxplug::cxxplug cxxlog::cxxlog)
    target_compile_definitions(${TEST_NAME} PRIVATE CXXLOG_LEVEL=cxxlog::verbose)

    gtest_add_tests(TARGET ${TEST_NAME} TEST_LIST TESTS)

    foreach(TEST_TARGET ${TESTS})
        set(TEST_ENV "CTEST_NAME=${TEST_TARGET}")
        list(APPEND TEST_ENV ${TEST_ENVIRONMENT})
        set_tests_properties(${TEST_TARGET} PROPERTIES ENVIRONMENT "${TEST_ENV}")
    endforeach()
endfunction()

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
