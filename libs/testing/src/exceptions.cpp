// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#include "quite/test/exceptions.hpp"
namespace quite::test
{
RemoteException::RemoteException(const Error &error)
    : std::runtime_error{error.message}
{}
} // namespace quite::test
