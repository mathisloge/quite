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

  private:
    std::shared_ptr<quite::RemoteObject> object_;
};
} // namespace test
} // namespace quite
