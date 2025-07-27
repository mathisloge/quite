

# File server.cpp



[**FileList**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**src**](dir_62c749a433f68b441b7c0425b5469d66.md) **>** [**probe**](dir_8a7b54f280cdd6b46c67f9938f379d86.md) **>** [**server.cpp**](protocol_2src_2probe_2server_8cpp.md)

[Go to the source code of this file](protocol_2src_2probe_2server_8cpp_source.md)



* `#include "quite/proto/probe/server.hpp"`
* `#include <thread>`
* `#include <exec/env.hpp>`
* `#include <exec/finally.hpp>`
* `#include <quite/logger.hpp>`
* `#include <quite/proto/health.grpc.pb.h>`
* `#include <quite/proto/meta_service.grpc.pb.h>`
* `#include <quite/proto/probe.grpc.pb.h>`
* `#include "rpc_fetch_windows.hpp"`
* `#include "rpc_find_object.hpp"`
* `#include "rpc_invoke_method.hpp"`
* `#include "rpc_meta_find_type.hpp"`
* `#include "rpc_mouse_injection.hpp"`
* `#include "rpc_object_properties.hpp"`
* `#include "rpc_set_object_property.hpp"`
* `#include "rpc_snapshot.hpp"`
* `#include <grpc++/server_builder.h>`
* `#include <agrpc/health_check_service.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**quite**](namespacequite.md) <br> |
| namespace | [**proto**](namespacequite_1_1proto.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**Impl**](classquite_1_1proto_1_1Server_1_1Impl.md) <br> |






















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DEFINE\_LOGGER**](#function-define_logger) (grpc\_server\_log) <br> |




























## Public Functions Documentation




### function DEFINE\_LOGGER 

```C++
DEFINE_LOGGER (
    grpc_server_log
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `libs/protocol/src/probe/server.cpp`

