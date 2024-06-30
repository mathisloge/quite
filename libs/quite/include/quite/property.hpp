#pragma once
#include <cstdint>
#include <string>
#include <variant>
#include <fmt/core.h>
#include "async_result.hpp"
#include "indirect.hpp"
#include "quitelib_export.h"

namespace quite
{
class RemoteObject;

using Value = std::
    variant<std::int64_t, double, bool, std::string, std::shared_ptr<RemoteObject>, xyz::indirect<struct ArrayObject>>;

struct ArrayObject
{
    std::vector<Value> values;
};
class QUITELIB_EXPORT Property
{
  public:
    virtual ~Property();
    virtual const std::string &name() const noexcept = 0;
    virtual const Result<Value> &value() const noexcept = 0;
    virtual AsyncResult<Value> read() noexcept = 0;
    virtual AsyncResult<Value> write(const Value &value) noexcept = 0;
};

using PropertyPtr = std::shared_ptr<Property>;
} // namespace quite
template <>
struct QUITELIB_EXPORT fmt::formatter<quite::Value> : formatter<string_view>
{
    auto format(const quite::Value &v, format_context &ctx) const -> format_context::iterator;
};
