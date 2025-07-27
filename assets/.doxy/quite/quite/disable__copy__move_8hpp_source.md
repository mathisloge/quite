

# File disable\_copy\_move.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**disable\_copy\_move.hpp**](disable__copy__move_8hpp.md)

[Go to the documentation of this file](disable__copy__move_8hpp.md)


```C++
#pragma once

#define QUITE_DISABLE_COPY(ClassName)                                                                                  \
    ClassName(const ClassName &) = delete;                                                                             \
    ClassName &operator=(const ClassName &) = delete;

#define QUITE_DISABLE_COPY_MOVE(ClassName)                                                                             \
    QUITE_DISABLE_COPY(ClassName)                                                                                      \
    ClassName(ClassName &&) = delete;                                                                                  \
    ClassName &operator=(ClassName &&) = delete;

#define QUITE_DEFAULT_MOVE(ClassName)                                                                                  \
    ClassName(ClassName &&) noexcept = default;                                                                        \
    ClassName &operator=(ClassName &&) noexcept = default;
```


