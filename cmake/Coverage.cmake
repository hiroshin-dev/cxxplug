#
# Copyright (c) 2022 Hiroshi Nakashima
#
# This software is released under the MIT License, see LICENSE.
#

find_program(LCOV_EXECUTABLE lcov)
find_program(GENHTML_EXECUTABLE genhtml)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS_COVERAGE
    "-g -O0 --coverage" CACHE STRING
    "Flags used by the C++ compiler during coverage builds."
    FORCE)
  set(CMAKE_C_FLAGS_COVERAGE
    "-g -O0 --coverage" CACHE STRING
    "Flags used by the C compiler during coverage builds."
    FORCE)
  mark_as_advanced(
    CMAKE_CXX_FLAGS_COVERAGE
    CMAKE_C_FLAGS_COVERAGE
  )
endif()

# add_coerage_target(<name>
#     [OUTPUT <output_dir>]
#     [TEST_COMMNAD <command> [args ...]]
#     [PATTERN <patterns> ...])
function(add_coverage_target TARGET_NAME)
  if(NOT CMAKE_COMPILER_IS_GNUCXX)
    return()
  endif()

  cmake_parse_arguments(COVERAGE "" "OUTPUT" "TEST_COMMAND;PATTERN" ${ARGN})
  if(NOT COVERAGE_OUTPUT)
    set(COVERAGE_OUTPUT ${TARGET_NAME})
  endif()
  if(NOT COVERAGE_TEST_COMMAND)
    set(COVERAGE_TEST_COMMAND ${CMAKE_CTEST_COMMAND})
  endif()
  if(NOT COVERAGE_PATTERN)
    set(EXTRACT_COMMAND
      ${CMAKE_COMMAND} -E copy coverage-merged.info coverage.info)
  else()
    set(EXTRACT_COMMAND
      ${LCOV_EXECUTABLE} --extract coverage-merged.info ${COVERAGE_PATTERN}
      -o coverage.info)
  endif()

  add_custom_target(${TARGET_NAME}
    # Cleanup lcov
    COMMAND ${LCOV_EXECUTABLE} --zerocounters -d ${PROJECT_SOURCE_DIR}
    # Capture lcov counters (before running tests)
    COMMAND ${LCOV_EXECUTABLE} --capture -d ${PROJECT_SOURCE_DIR}
      --no-external -i -o coverage-before.info
    # Run tests
    COMMAND ${COVERAGE_TEST_COMMAND}
    # Capture lcov counters (after running tests)
    COMMAND ${LCOV_EXECUTABLE} --capture -d ${PROJECT_SOURCE_DIR}
      --no-external -o coverage-after.info
    # Combine coverage info
    COMMAND ${LCOV_EXECUTABLE} -a coverage-before.info -a coverage-after.info
      -o coverage-merged.info
    # Extract coverage info
    COMMAND ${EXTRACT_COMMAND}
    # Generate html report
    COMMAND ${GENHTML_EXECUTABLE} -o ${COVERAGE_OUTPUT} coverage.info
    # Remove coverage info
    COMMAND ${CMAKE_COMMAND} -E remove
      coverage-before.info coverage-after.info coverage-merged.info
      coverage.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  )
endfunction()
