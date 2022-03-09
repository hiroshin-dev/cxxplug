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
    set(BUILD_EXAMPLES ON)
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
    PUBLIC include
    PRIVATE src
)
target_link_libraries(cxxplug PRIVATE cxxlog::cxxlog)
target_compile_definitions(cxxplug PRIVATE CXXLOG_LEVEL=cxxlog::debug)
if(MSVC)
    target_compile_options(cxxplug PRIVATE /W4)
else()
    target_link_libraries(cxxplug PRIVATE dl)
    target_compile_options(cxxplug PRIVATE -Wall -Wextra -Wpedantic)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
