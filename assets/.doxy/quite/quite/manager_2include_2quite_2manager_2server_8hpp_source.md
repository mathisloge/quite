

# File server.hpp

[**File List**](files.md) **>** [**include**](dir_4016f4d3acd3fc8991c53702cd4dc6d5.md) **>** [**quite**](dir_b37ea4b54adf6aca6f6e7e088c5d43d6.md) **>** [**manager**](dir_3f8205de661b2b55b021bbc49d05e58b.md) **>** [**server.hpp**](manager_2include_2quite_2manager_2server_8hpp.md)

[Go to the documentation of this file](manager_2include_2quite_2manager_2server_8hpp.md)


```C++
#pragma once
#include <memory>
#include <quite/disable_copy_move.hpp>

namespace quite::manager
{
class Server final
{
  public:
    QUITE_DISABLE_COPY(Server);
    QUITE_DEFAULT_MOVE(Server);

    Server();
    ~Server();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
} // namespace quite::manager
```


