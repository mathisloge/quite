// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <memory>
#include <quite/disable_copy_move.hpp>

namespace quite::manager
{
class Server final
{
  public:
    QUITE_DISABLE_COPY(Server);
    QUITE_DEFAULT_MOVE(Server);

    Server();
    ~Server();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::manager
