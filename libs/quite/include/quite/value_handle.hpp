#pragma once
#include <cstdint>
#include <string>
#include <variant>
#include "quitelib_export.h"
struct ValueHandle
{
    std::string value;
}; // some kind of any datatype

struct Property
{
    std::string name;
    ValueHandle value;
};

namespace quite
{
class QUITELIB_EXPORT Value
{
  public:
    using Type = std::variant<bool, std::int64_t, double, std::string>;
    virtual ~Value();

    virtual Type value() const = 0;

    std::string to_str();

  protected:
    Value();
};
} // namespace quite
