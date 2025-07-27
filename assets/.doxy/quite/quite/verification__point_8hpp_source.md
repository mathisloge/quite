

# File verification\_point.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**include**](dir_69eac062172cc3dd38536daddef8f6c7.md) **>** [**quite**](dir_4b2f86ac1ca33b50681e1a9febdc0774.md) **>** [**client**](dir_7d6276c65eb2c4014d2f0c2cacdec3f0.md) **>** [**testing**](dir_c6e9347de3fb4db939a0e8cd4d8d8ee5.md) **>** [**verification\_point.hpp**](verification__point_8hpp.md)

[Go to the documentation of this file](verification__point_8hpp.md)


```C++
#pragma once
#include "quite/async_result.hpp"
#include "quite/client/remote_object.hpp"
#include "quite/quite_client_export.hpp"

namespace quite::testing
{

[[nodiscard]] QUITE_CLIENT_EXPORT bool has_verification_point(const std::string &name);
QUITE_CLIENT_EXPORT AsyncResult<void> create_verification_point(client::RemoteObjectPtr object,
                                                                const std::string &name);
QUITE_CLIENT_EXPORT AsyncResult<bool> verify_verification_point(client::RemoteObjectPtr object,
                                                                const std::string &name);

} // namespace quite::testing
```


