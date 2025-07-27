

# File configure\_client\_context.cpp

[**File List**](files.md) **>** [**client**](dir_5522d6aca5c3fb454e911c5582f2e576.md) **>** [**configure\_client\_context.cpp**](configure__client__context_8cpp.md)

[Go to the documentation of this file](configure__client__context_8cpp.md)


```C++
#include "configure_client_context.hpp"

namespace quite::proto
{
void configure_client_context(grpc::ClientContext &client_context)
{
    client_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds{10});
    client_context.set_wait_for_ready(true);
}
} // namespace quite::proto
```


