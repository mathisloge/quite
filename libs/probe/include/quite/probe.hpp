// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <string>
#include "quite/quite_probe_export.hpp"

namespace quite
{
struct GrpcServer
{
    //! TODO: add potential secure channels
    std::string server_address;
};

class PROBE_EXPORT Probe
{
  public:
    virtual ~Probe();
};
} // namespace quite
