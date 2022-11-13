// SPDX-FileCopyrightText: Fondazione Istituto Italiano di Tecnologia (IIT)
// SPDX-License-Identifier: BSD-3-Clause

#include <cstdlib>
#include <iostream>
#include <filesystem>

#include <reloc_cpp_test_shared.h>
#include <reloc_cpp_test_static.h>
#include <reloc_cpp_test_shared_relocatable_disabled.h>
#include <reloc_cpp_test_cmake_variables.h>

std::string toCanonical(const std::string input_path)
{
    return std::filesystem::weakly_canonical(std::filesystem::path(input_path)).string();
}

int main()
{
    std::string sharedInstallPrefix = RelocCPP::test::sharedlib::getInstallPrefix().value();
    std::string staticInstallPrefix = RelocCPP::test::staticlib::getInstallPrefix().value();;
    std::string sharedRelocatableDisabledInstallPrefix = getInstallPrefixSharedRelocatableDisabled().value();

    std::cerr << "reloc-cpp test:" << std::endl;
    std::cerr << "sharedInstallPrefix: " << sharedInstallPrefix << std::endl;
    std::cerr << "CMAKE_BINARY_DIR: " << CMAKE_BINARY_DIR << std::endl;
    std::cerr << "staticInstallPrefix: " << staticInstallPrefix << std::endl;
    std::cerr << "CMAKE_INSTALL_PREFIX: " << CMAKE_INSTALL_PREFIX << std::endl;
    std::cerr << "sharedRelocatableDisabledInstallPrefix: " << sharedRelocatableDisabledInstallPrefix << std::endl;


    if (toCanonical(sharedInstallPrefix) != toCanonical(CMAKE_BINARY_DIR))
    {
        std::cerr << "getInstallPrefixShared returned unexpected value, test is failing." << std::endl;
        return EXIT_FAILURE;
    }

    if (toCanonical(staticInstallPrefix) != toCanonical(CMAKE_INSTALL_PREFIX))
    {
        std::cerr << "getInstallPrefixStatic returned unexpected value, test is failing." << std::endl;
        return EXIT_FAILURE;
    }

    if (toCanonical(sharedRelocatableDisabledInstallPrefix) != toCanonical(CMAKE_INSTALL_PREFIX))
    {
        std::cerr << "getInstallPrefixSharedRelocatableDisabled returned unexpected value, test is failing." << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
