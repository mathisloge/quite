#pragma once
#include <memory>
#include "remote_object.hpp"

namespace quite::test
{
struct IExpectBuilder
{
    virtual ~IExpectBuilder() = default;
    virtual bool to_have_screenshot() = 0;
};

std::unique_ptr<IExpectBuilder> expect(RemoteObject remote_object);
} // namespace quite::test
