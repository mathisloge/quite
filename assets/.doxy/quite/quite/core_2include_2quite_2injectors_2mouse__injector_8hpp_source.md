

# File mouse\_injector.hpp

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**include**](dir_25de89a49d1da2858ac6330785c12b40.md) **>** [**quite**](dir_6f50b8774c4552618988001c2022dcf6.md) **>** [**injectors**](dir_3608ef6849ab2123a7cae9eea604e8ae.md) **>** [**mouse\_injector.hpp**](core_2include_2quite_2injectors_2mouse__injector_8hpp.md)

[Go to the documentation of this file](core_2include_2quite_2injectors_2mouse__injector_8hpp.md)


```C++
#pragma once
#include "keys.hpp"
#include "quite/async_result.hpp"
#include "quite/geometry.hpp"
#include "quite/quite_core_export.hpp"
#include "quite/value/object_id.hpp"

namespace quite::core
{

struct MouseAction
{
    Vector2 position;
    MouseButton button;
    MouseTrigger trigger;
    KeyboardModifier modifier;
};

class QUITE_CORE_EXPORT IMouseInjector
{
  public:
    virtual ~IMouseInjector() = default;
    virtual AsyncResult<void> single_action(ObjectId target_id, MouseAction action) = 0;
};
} // namespace quite::core
```


