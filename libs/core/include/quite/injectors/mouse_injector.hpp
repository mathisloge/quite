#pragma once
#include "keys.hpp"
#include "quite/geometry.hpp"

namespace quite::core
{

struct MouseAction
{
    Vector2 position;
    MouseTrigger trigger;
    MouseButton button;
    KeyboardModifier modifier;
};

class IMouseInjector
{};
} // namespace quite::core
