// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#cmakedefine01 QUITE_USES_BOOST

#if QUITE_USES_BOOST
#include <boost/asio.hpp>
#include <boost/system/errc.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#define QUITE_ASIO_NAMESPACE boost::asio
#else
#include <system_error>
#include <asio.hpp>
#define QUITE_ASIO_NAMESPACE asio
#endif

namespace quite
{
#if QUITE_USES_BOOST
namespace asio_impl = ::boost::asio;
using error_code = ::boost::system::error_code;
using error_condition = ::boost::system::error_condition;
namespace errc = ::boost::system::errc;
using system_error = ::boost::system::system_error;
#else
namespace asio_impl = ::asio;
using error_code = std::error_code;
using error_condition = std::error_condition;
using errc = std::errc;
using system_error = std::system_error;
#endif
} // namespace quite
