#pragma once
#include <cstdint>
#include <string>
#include <variant>
#include <fmt/core.h>
#include "async_result.hpp"
#include "quitelib_export.h"

namespace quite
{
using Value = std::variant<std::int64_t, double, bool, std::string>;
class QUITELIB_EXPORT Property
{
  public:
    virtual ~Property();
    virtual const std::string &name() const noexcept = 0;
    virtual const Result<Value> &value() const noexcept = 0;
    virtual AsyncResult<Value> read() noexcept = 0;
    virtual AsyncResult<Value> write(const Value &value) noexcept = 0;
};
} // namespace quite
template <>
struct QUITELIB_EXPORT fmt::formatter<std::variant<std::int64_t, double, bool, std::string>> : formatter<string_view>
{
    auto format(const quite::Value &v, format_context &ctx) const -> format_context::iterator;
};
