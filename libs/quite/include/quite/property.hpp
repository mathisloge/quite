#pragma once
#include <string>
#include <fmt/core.h>
#include <quite/async_result.hpp>
#include <quite/meta/meta_type_id.hpp>
#include "quite/quite_client_export.hpp"
#include "value.hpp"

namespace quite
{

struct ArrayObject
{
    std::vector<Value> values;
};

struct ClassMember
{
    std::string name;
    Value value;
};

struct ClassObject
{
    std::string type_name;
    std::vector<ClassMember> members;
};

class QUITE_CLIENT_EXPORT Property
{
  public:
    virtual ~Property();
    virtual const std::string &name() const = 0;
    virtual meta::TypeId type_id() const = 0;
    virtual const Result<Value> &value() const = 0;
    virtual AsyncResult<Value> read() = 0;
    virtual AsyncResult<Value> write(const Value &value) = 0;
};

using PropertyPtr = std::shared_ptr<Property>;
} // namespace quite
template <>
struct QUITE_CLIENT_EXPORT fmt::formatter<quite::Value> : formatter<string_view>
{
    auto format(const quite::Value &v, format_context &ctx) const -> format_context::iterator;
};
