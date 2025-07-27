// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <stdexcept>
#include <quite/error.hpp>
#include "quite/quite_test_export.hpp"

namespace quite::test
{
class QUITE_TEST_EXPORT RemoteException : public std::runtime_error
{
  public:
    explicit RemoteException(const Error &error);
};
} // namespace quite::test
