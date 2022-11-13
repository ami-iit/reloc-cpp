# reloc-cpp

CMake/C++ library to get the installation prefix of a shared library in a relocatable way.

In a nutshell, it permits to avoid the need to hardcode the location of `CMAKE_INSTALL_PREFIX` in a shared library if you need it to localize other resources installed with the package. This permits to easily move the installation prefix in a location different from `CMAKE_INSTALL_PREFIX` after the installation (i.e. making it a *relocatable* installation), as long as the library is compiled as shared.

In the case that the library is compiled as static, `reloc-cpp` will fall back to hardcode `CMAKE_INSTALL_PREFIX`  in the library.

## Installation

### FetchContent

~~~cmake
include(FetchContent)
FetchContent_Declare(
  reloc-cpp
  GIT_REPOSITORY https://github.com/ami-iit/reloc-cpp.git
  GIT_TAG        <used_tag>
)

FetchContent_MakeAvailable(reloc-cpp)
~~~

## Usage

In your CMake build system you can use `reloc-cpp` as:

```cmake
add_library(yourLibrary)

# ...

reloc_cpp_generate(yourLibrary
                   GENERATED_HEADER ${CMAKE_CURRENT_BINARY_DIR}/yourLibrary_getInstallPrefix.h
                   GENERATED_FUNCTION yourLibrary::getInstallPrefix)
```

then, you can use it in C++ as:

~~~cpp
#include <yourLibrary_getInstallationPrefix.h>

// This return the value corresponding to CMAKE_INSTALL_PREFIX
std::string installPrefix = yourLibrary::getInstallPrefix().value();
~~~


## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

## License

[BSD-3-Clause](https://choosealicense.com/licenses/bsd-3-clause/)
