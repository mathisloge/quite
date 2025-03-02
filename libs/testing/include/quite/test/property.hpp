#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include "quite/quite_test_export.hpp"

namespace quite
{
class Property;
}
namespace quite::test
{
class QUITE_TEST_EXPORT Property final
{
  public:
    explicit Property(std::shared_ptr<quite::Property> property);

    using Value = std::variant<bool, std::uint64_t, std::int64_t, double, std::string>;
    Value fetch();
    const Value &value() const;
    void write(Value value);

  private:
    std::shared_ptr<quite::Property> property_;
};
} // namespace quite::test
