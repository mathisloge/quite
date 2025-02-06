#pragma once
#include <stdexcept>
#include <quite/error.hpp>
#include "quite_test_export.hpp"

namespace quite::test
{
class QUITE_TEST_EXPORT RemoteException : public std::runtime_error
{
  public:
    explicit RemoteException(const Error &error);
};
} // namespace quite::test
