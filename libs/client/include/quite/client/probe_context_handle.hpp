// SPDX-FileCopyrightText: 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <memory>
#include "quite/quite_client_export.hpp"
namespace quite::client
{
class ProbeContext;
class QUITE_CLIENT_EXPORT ProbeContextHandle
{
  public:
    explicit ProbeContextHandle(std::shared_ptr<ProbeContext> probe_context);
    ProbeContext *operator->();

  private:
    std::shared_ptr<ProbeContext> probe_context_;
};
} // namespace quite::client
