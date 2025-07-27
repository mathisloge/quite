

# File logger.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**logger.hpp**](logger_8hpp.md)

[Go to the documentation of this file](logger_8hpp.md)


```C++
#pragma once
#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include "quite/quite_core_export.hpp"

namespace quite
{
QUITE_CORE_EXPORT quill::Logger *create_logger(std::string_view logger_name);
}

#define DEFINE_LOGGER(name)                                                                                            \
    namespace                                                                                                          \
    {                                                                                                                  \
    auto name()                                                                                                        \
    {                                                                                                                  \
        static const auto &&name_logger = ::quite::create_logger(#name);                                               \
        return name_logger;                                                                                            \
    }                                                                                                                  \
    }
```


