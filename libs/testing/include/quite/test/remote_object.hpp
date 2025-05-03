#pragma once
#include <memory>
#include <quite/image.hpp>
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
    void invoke_method(std::string method_name);
    [[nodiscard]] Image take_snapshot();
    [[nodiscard]] Property property(std::string name);

    [[nodiscard]] bool operator==(const RemoteObject &rhs) const;

    std::shared_ptr<quite::RemoteObject> underlying_object();

  private:
    std::shared_ptr<quite::RemoteObject> object_;
};
} // namespace test
} // namespace quite
