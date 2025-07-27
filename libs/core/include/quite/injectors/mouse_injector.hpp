// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

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
