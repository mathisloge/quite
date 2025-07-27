

# File error\_helper.hpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**error\_helper.hpp**](error__helper_8hpp.md)

[Go to the documentation of this file](error__helper_8hpp.md)


```C++
#pragma once
#include <grpcpp/support/status.h>
#include <quite/error.hpp>

namespace quite::proto
{
grpc::Status result2grpc_status(const Error &error);
Error grpc_status2result(const grpc::Status &error);
} // namespace quite::proto
```


