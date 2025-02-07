#pragma once
#include <string>
#include <vector>

namespace quite::proto
{
enum class Traits
{
    unpack_properties = 0x01
};

using PropertyNames = std::vector<std::string>;
}; // namespace quite::proto
