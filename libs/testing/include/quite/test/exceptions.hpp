#pragma once
#include <stdexcept>
#include "quite_test_export.hpp"

namespace quite::test
{
class NotFoundException : public std::runtime_error
{};
} // namespace quite::test
