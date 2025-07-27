// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once

#define QUITE_DISABLE_COPY(ClassName)                                                                                  \
    ClassName(const ClassName &) = delete;                                                                             \
    ClassName &operator=(const ClassName &) = delete;

#define QUITE_DISABLE_COPY_MOVE(ClassName)                                                                             \
    QUITE_DISABLE_COPY(ClassName)                                                                                      \
    ClassName(ClassName &&) = delete;                                                                                  \
    ClassName &operator=(ClassName &&) = delete;

#define QUITE_DEFAULT_MOVE(ClassName)                                                                                  \
    ClassName(ClassName &&) noexcept = default;                                                                        \
    ClassName &operator=(ClassName &&) noexcept = default;
