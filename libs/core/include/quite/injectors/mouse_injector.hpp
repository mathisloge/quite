// SPDX-FileCopyrightText: 2025, 2026 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include "quite/async_result.hpp"
#include "quite/core/bit_flags.hpp"
#include "quite/geometry.hpp"
#include "quite/keyboard.hpp"
#include "quite/mouse.hpp"
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
    virtual AsyncResult<void> perfom_on_target(ObjectId target_id,
                                               MouseTrigger trigger,
                                               MouseButton button,
                                               MouseEventOptions options = {}) = 0;
    virtual AsyncResult<void> single_action(ObjectId target_id, MouseAction action) = 0;
};
} // namespace quite::core
