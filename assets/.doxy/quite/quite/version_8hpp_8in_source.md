

# File version.hpp.in

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**version.hpp.in**](version_8hpp_8in.md)

[Go to the documentation of this file](version_8hpp_8in.md)


```C++
#pragma once
#include <string_view>
namespace quite
{
inline constexpr unsigned int kVersionMajor = @PROJECT_VERSION_MAJOR@;
inline constexpr unsigned int kVersionMinor = @PROJECT_VERSION_MINOR@;
inline constexpr unsigned int kVersionPatch = @PROJECT_VERSION_PATCH@;
inline constexpr std::string_view kVersion = "@PROJECT_VERSION@";
inline constexpr std::string_view kGitRef = "@git_sha@";
inline constexpr std::string_view kGitBranch = "@git_branch@";


inline constexpr std::string_view kRuntimeDir = "@CMAKE_RUNTIME_OUTPUT_DIRECTORY@";
} // namespace protodoc
```


