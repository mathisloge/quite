

# File remote\_object.hpp

[**File List**](files.md) **>** [**include**](dir_0e3ab90749f7b4be0e4eb22d010aec3d.md) **>** [**quite**](dir_4b2197acd3cfc200796c46ec50ed103f.md) **>** [**test**](dir_e2259a6ae36431ad829e5c40f57eb4d8.md) **>** [**remote\_object.hpp**](testing_2include_2quite_2test_2remote__object_8hpp.md)

[Go to the documentation of this file](testing_2include_2quite_2test_2remote__object_8hpp.md)


```C++
#pragma once
#include <memory>
#include <quite/image.hpp>
#include "property.hpp"
#include "quite/quite_test_export.hpp"

namespace quite
{
namespace client
{
class RemoteObject;
}

namespace test
{
class QUITE_TEST_EXPORT RemoteObject
{
  public:
    explicit RemoteObject(std::shared_ptr<client::RemoteObject> object);

    void mouse_action();
    void invoke_method(std::string method_name);
    [[nodiscard]] Image take_snapshot();
    [[nodiscard]] Property property(std::string name);

    [[nodiscard]] bool operator==(const RemoteObject &rhs) const;

    std::shared_ptr<client::RemoteObject> underlying_object();

  private:
    std::shared_ptr<client::RemoteObject> object_;
};
} // namespace test
} // namespace quite
```


