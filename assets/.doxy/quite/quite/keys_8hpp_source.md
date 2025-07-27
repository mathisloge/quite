

# File keys.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**injectors**](dir_3608ef6849ab2123a7cae9eea604e8ae.md) **>** [**keys.hpp**](keys_8hpp.md)

[Go to the documentation of this file](keys_8hpp.md)


```C++
#pragma once
namespace quite::core
{
enum class MouseTrigger
{
    none,
    click,
    double_click,
    press,
    release,
    move
};

enum class MouseButton
{
    none,
    left,
    right,
    middle,
    forward,
    back,
};

enum class KeyboardModifier
{
    none,
    shift,
    control,
    alt,
    meta,
};
} // namespace quite::core
```


