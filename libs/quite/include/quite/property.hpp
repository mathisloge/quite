#pragma once
#include <cstdint>
#include <string>
#include <variant>
#include "async_result.hpp"
#include "quitelib_export.h"

namespace quite
{
class QUITELIB_EXPORT Property
{
  public:
    using Value = std::variant<std::int64_t, double, bool, std::string>;

    virtual ~Property();
    virtual AsyncResult<Value> read() = 0;
    virtual AsyncResult<Value> write(const Value &value) = 0;
};
} // namespace quite
