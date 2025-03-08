#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include "quite/quite_test_export.hpp"

namespace quite
{
class ObjectQuery;
}
namespace quite::test
{
class QUITE_TEST_EXPORT ObjectQueryBuilder
{
  public:
    ObjectQueryBuilder();

    ObjectQueryBuilder &set_parent(const ObjectQueryBuilder &parent);

    ObjectQueryBuilder &add_property(std::string key, std::int64_t value);

    ObjectQueryBuilder &add_property(std::string key, double value);

    ObjectQueryBuilder &add_property(std::string key, bool value);

    ObjectQueryBuilder &add_property(std::string key, std::string value);

    std::shared_ptr<ObjectQuery> create();

  private:
    std::shared_ptr<ObjectQuery> query_;
};
} // namespace quite::test
