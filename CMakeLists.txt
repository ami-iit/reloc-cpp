# SPDX-FileCopyrightText: Fondazione Istituto Italiano di Tecnologia (IIT)
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required(VERSION 3.16)

project(reloc-cpp
        LANGUAGES CXX C
        VERSION 0.1.0)

include(GNUInstallDirs)

# Make reloc_cpp_generate available
include(${CMAKE_CURRENT_SOURCE_DIR}/RelocCPPGenerate.cmake)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(RELOC_CPP_STANDALONE ON)
endif()

option(RELOC_CPP_INSTALL "Enable installation of reloc-cpp" ${RELOC_CPP_STANDALONE})

# Build test related commands?
option(BUILD_TESTING "Create tests using CMake" ${RELOC_CPP_STANDALONE})
if(BUILD_TESTING)
  enable_testing()
endif()

if(RELOC_CPP_INSTALL)
  set(RELOC_CPP_INSTALL_MODULE_DIR "${CMAKE_INSTALL_DATADIR}/reloc-cpp")
  set(RELOC_CPP_INSTALL_CMAKE_DIR "${CMAKE_INSTALL_DATADIR}/reloc-cpp/cmake")

  install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/RelocCPPGenerate.cmake
          DESTINATION "${CMAKE_INSTALL_DATADIR}/reloc-cpp")

  find_package(YCM REQUIRED)
  include(InstallBasicPackageFiles)
  install_basic_package_files(${PROJECT_NAME}
                              VERSION ${${PROJECT_NAME}_VERSION}
                              COMPATIBILITY AnyNewerVersion
                              VARS_PREFIX ${PROJECT_NAME}
                              NO_CHECK_REQUIRED_COMPONENTS_MACRO
                              ARCH_INDEPENDENT
                              NO_EXPORT)
  include(AddUninstallTarget)
endif()

# Add integration tests (unit tests for each library should be in each sublibrary directory).
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
