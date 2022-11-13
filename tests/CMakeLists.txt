# SPDX-FileCopyrightText: Fondazione Istituto Italiano di Tecnologia (IIT)
# SPDX-License-Identifier: BSD-3-Clause

# For the tests, we make sure that the relative path in the build location is the same
# of the install, and we make sure that the value returned by the shared library is ${CMAKE_BINARY_DIR}
# while for the static library we make sure that the value returned is ${CMAKE_INSTALL_PREFIX}
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

# shared test
add_library(reloc-cpp-test-shared SHARED)

reloc_cpp_generate(reloc-cpp-test-shared
                   GENERATED_HEADER ${CMAKE_CURRENT_BINARY_DIR}/reloc_cpp_test_shared.h
                   GENERATED_FUNCTION RelocCPP::test::sharedlib::getInstallPrefix)
set_target_properties(reloc-cpp-test-shared PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# static test
add_library(reloc-cpp-test-static STATIC)

reloc_cpp_generate(reloc-cpp-test-static
                   GENERATED_HEADER ${CMAKE_CURRENT_BINARY_DIR}/reloc_cpp_test_static.h
                   GENERATED_FUNCTION RelocCPP::test::staticlib::getInstallPrefix)

# shared-relocatable-disabled
# In this case, we test the use of several options:
# * DISABLE_RELOCATABLE
# Use of function without namespace
add_library(reloc-cpp-test-shared-relocatable-disabled SHARED)

reloc_cpp_generate(reloc-cpp-test-shared-relocatable-disabled
                   GENERATED_HEADER ${CMAKE_CURRENT_BINARY_DIR}/reloc_cpp_test_shared_relocatable_disabled.h
                   GENERATED_FUNCTION getInstallPrefixSharedRelocatableDisabled
                   DISABLE_RELOCATABLE ON)
set_target_properties(reloc-cpp-test-shared-relocatable-disabled PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Write header with CMake variables to check
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/reloc_cpp_test_cmake_variables.h
"#pragma once

#define CMAKE_INSTALL_PREFIX \"${CMAKE_INSTALL_PREFIX}\"
#define CMAKE_BINARY_DIR \"${CMAKE_BINARY_DIR}\"

")

# Add test executable
add_executable(reloc-cpp-test reloc_cpp_test.cpp)
target_include_directories(reloc-cpp-test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(reloc-cpp-test PRIVATE reloc-cpp-test-shared reloc-cpp-test-static reloc-cpp-test-shared-relocatable-disabled)
add_test(NAME reloc-cpp-test COMMAND reloc-cpp-test)
