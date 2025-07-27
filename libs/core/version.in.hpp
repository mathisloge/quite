// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <string_view>
namespace quite
{
inline constexpr unsigned int kVersionMajor = @PROJECT_VERSION_MAJOR @;
inline constexpr unsigned int kVersionMinor = @PROJECT_VERSION_MINOR @;
inline constexpr unsigned int kVersionPatch = @PROJECT_VERSION_PATCH @;
inline constexpr std::string_view kVersion = "@PROJECT_VERSION@";
inline constexpr std::string_view kGitRef = "@git_sha@";
inline constexpr std::string_view kGitBranch = "@git_branch@";

inline constexpr std::string_view kRuntimeDir = "@CMAKE_RUNTIME_OUTPUT_DIRECTORY@";
} // namespace quite
