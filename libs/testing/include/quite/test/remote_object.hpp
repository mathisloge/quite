#pragma once
#include <memory>
#include "property.hpp"
#include "quite/quite_test_export.hpp"

namespace quite
{
class RemoteObject;

namespace test
{
class QUITE_TEST_EXPORT RemoteObject
{
  public:
    explicit RemoteObject(std::shared_ptr<quite::RemoteObject> object);

    void mouse_action();
    void take_snapshot();
    void invoke_method(std::string method_name);
    Property property(std::string name);

  private:
    std::shared_ptr<quite::RemoteObject> object_;
};
} // namespace test
} // namespace quite
