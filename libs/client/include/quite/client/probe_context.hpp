// SPDX-FileCopyrightText: 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <quite/injectors/mouse_injector.hpp>
#include "quite/quite_client_export.hpp"

namespace quite::client
{
class QUITE_CLIENT_EXPORT ProbeContext
{
  public:
    virtual core::IMouseInjector &mouse_injector() = 0;
};
} // namespace quite::client
