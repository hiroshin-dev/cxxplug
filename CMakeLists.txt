#
# Copyright (c) 2022 Hiroshi Nakashima
#
# This software is released under the MIT License, see LICENSE.
#
cmake_minimum_required(VERSION 3.11)

project(cxxplug VERSION 0.1.0)
message(STATUS "${PROJECT_NAME} ${PROJECT_VERSION}")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(ProjectVersion)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

if(UNIX)
    # CTest configuration variables must be set before `include(CTest)`
    set(MEMORYCHECK_COMMAND_OPTIONS
        "${MEMORYCHECK_COMMAND_OPTIONS} --leak-check=full --show-reachable=yes --num-callers=50")
    set(MEMORYCHECK_COMMAND_OPTIONS
        "${MEMORYCHECK_COMMAND_OPTIONS} --xml=yes --xml-file=${CMAKE_BINARY_DIR}/Testing/valgrind_%q{CTEST_NAME}.xml")
endif()

option(BUILD_EXAMPLES "build all examples" OFF)

# option(BUILD_TESTING) & enable_testing()
include(CTest)
if(BUILD_TESTING)
    include(Coverage)
    add_coverage_target(coverage
        PATTERN
            *cxxplug/include*
            *cxxplug/src*
    )
endif()

if(MSVC)
    set(WARNING_OPTIONS /W4)
else()
    set(WARNING_OPTIONS -Wall -Wextra -Wpedantic)
endif()

include(FetchContent)
FetchContent_Declare(
    cxxlog
    URL https://github.com/hiroshin-dev/cxxlog/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(cxxlog)

configure_file(
    ${PROJECT_SOURCE_DIR}/src/version/version.cxx.in
    ${PROJECT_SOURCE_DIR}/src/version/version.cxx
    @ONLY
)

add_library(cxxplug SHARED
    src/plugin.cxx
    src/utils.cxx
    src/version/version.cxx
)
add_library(cxxplug::cxxplug ALIAS cxxplug)

target_include_directories(cxxplug
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE src
)
target_link_libraries(cxxplug PRIVATE cxxlog::cxxlog)
target_compile_definitions(cxxplug PRIVATE CXXLOG_LEVEL=cxxlog::debug)
target_compile_options(cxxplug PRIVATE ${WARNING_OPTIONS})
if(UNIX)
    target_link_libraries(cxxplug PRIVATE dl)
endif()
set_target_properties(cxxplug PROPERTIES VERSION ${PROJECT_VERSION})

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

install(TARGETS cxxplug
    EXPORT cxxplug-config
)
install(EXPORT cxxplug-config
    NAMESPACE cxxplug::
    DESTINATION lib/cmake/cxxplug
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION include
)
