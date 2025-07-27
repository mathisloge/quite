// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include "quite/async_result.hpp"
#include "quite/client/remote_object.hpp"
#include "quite/quite_client_export.hpp"

namespace quite::testing
{

[[nodiscard]] QUITE_CLIENT_EXPORT bool has_verification_point(const std::string &name);
QUITE_CLIENT_EXPORT AsyncResult<void> create_verification_point(client::RemoteObjectPtr object,
                                                                const std::string &name);
QUITE_CLIENT_EXPORT AsyncResult<bool> verify_verification_point(client::RemoteObjectPtr object,
                                                                const std::string &name);

} // namespace quite::testing
