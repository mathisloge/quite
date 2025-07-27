// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <memory>
#include "quite/quite_test_export.hpp"
#include "remote_object.hpp"

namespace quite::test
{
struct QUITE_TEST_EXPORT IExpectBuilder
{
    virtual ~IExpectBuilder() = default;
    virtual bool to_have_screenshot(const std::string &name) = 0;
};

[[nodiscard]] QUITE_TEST_EXPORT std::unique_ptr<IExpectBuilder> expect(RemoteObject remote_object);
} // namespace quite::test
