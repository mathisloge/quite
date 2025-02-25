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
