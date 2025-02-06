#pragma once
#include <memory>
#include "quite_test_export.hpp"

namespace quite
{
class RemoteObject;

namespace test
{
class QUITE_TEST_EXPORT RemoteObject
{
  public:
    explicit RemoteObject(std::shared_ptr<quite::RemoteObject> object);

    // todo: should this be a free standing function taking a remote object?
    void mouse_action();
    void take_snapshot();

  private:
    std::shared_ptr<quite::RemoteObject> object_;
};
} // namespace test
} // namespace quite
