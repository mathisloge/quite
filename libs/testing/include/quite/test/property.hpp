#pragma once
#include <chrono>
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
class RemoteObject;

class QUITE_TEST_EXPORT Property final
{
  public:
    explicit Property(std::shared_ptr<quite::Property> property);

    using Value = std::variant<bool, std::uint64_t, std::int64_t, double, std::string, RemoteObject>;
    Property::Value fetch();
    Property::Value value() const;
    /**
     * @brief Waits until the given target value has been reached or the time has been passed. Returns either the target
     * value or the last fetched value after a timeout.
     *
     * @param target_value the desired value
     * @param timeout max time to wait
     * @return Property::Value either the target value or the last fetched value after a timeout
     */
    Property::Value wait_for_value(Property::Value target_value, std::chrono::milliseconds timeout);

    void write(Property::Value value);

  private:
    std::shared_ptr<quite::Property> property_;
};
} // namespace quite::test
