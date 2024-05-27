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
    using Value = std::variant<bool, std::int64_t, double, std::string>;

    virtual ~Property();
    virtual AsyncResult<Value> read() = 0;
    virtual AsyncResult<bool> write(const Value &value) = 0;
};
} // namespace quite
