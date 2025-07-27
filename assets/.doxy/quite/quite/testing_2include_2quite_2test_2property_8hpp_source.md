

# File property.hpp

[**File List**](files.md) **>** [**include**](dir_0e3ab90749f7b4be0e4eb22d010aec3d.md) **>** [**quite**](dir_4b2197acd3cfc200796c46ec50ed103f.md) **>** [**test**](dir_e2259a6ae36431ad829e5c40f57eb4d8.md) **>** [**property.hpp**](testing_2include_2quite_2test_2property_8hpp.md)

[Go to the documentation of this file](testing_2include_2quite_2test_2property_8hpp.md)


```C++
#pragma once
#include <chrono>
#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include "quite/quite_test_export.hpp"

namespace quite::client
{
class Property;
}

namespace quite::test
{
class RemoteObject;

class QUITE_TEST_EXPORT Property final
{
  public:
    explicit Property(std::shared_ptr<client::Property> property);

    using Value = std::variant<bool, std::uint64_t, std::int64_t, double, std::string, RemoteObject>;
    Property::Value fetch();
    Property::Value value() const;
    Property::Value wait_for_value(Property::Value target_value, std::chrono::milliseconds timeout);

    void write(Property::Value value);

  private:
    std::shared_ptr<client::Property> property_;
};
} // namespace quite::test
```


