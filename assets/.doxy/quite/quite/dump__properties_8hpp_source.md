

# File dump\_properties.hpp

[**File List**](files.md) **>** [**client**](dir_66fcfc6cbdc0959ca004c79e577b2983.md) **>** [**include**](dir_69eac062172cc3dd38536daddef8f6c7.md) **>** [**quite**](dir_4b2f86ac1ca33b50681e1a9febdc0774.md) **>** [**client**](dir_7d6276c65eb2c4014d2f0c2cacdec3f0.md) **>** [**utils**](dir_40c584c53b41f36667c6f7a7f0c7366b.md) **>** [**dump\_properties.hpp**](dump__properties_8hpp.md)

[Go to the documentation of this file](dump__properties_8hpp.md)


```C++
#pragma once
#include <nlohmann/json_fwd.hpp>
#include "quite/client/remote_object.hpp"
#include "quite/quite_client_export.hpp"
namespace quite::client
{
AsyncResult<nlohmann::json> QUITE_CLIENT_EXPORT dump_properties(RemoteObjectPtr remote_object,
                                                                std::vector<std::string> properties);
}
```


