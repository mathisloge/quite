#pragma once
#include <unordered_set>
#include "keyboard.hpp"
#include "quite/async_result.hpp"
#include "quite/quite_core_export.hpp"
#include "quite/value/object_id.hpp"

namespace quite::core
{

class QUITE_CORE_EXPORT IKeyboardInjector
{
  public:
    using KeyStates = std::unordered_set<KeyboardKey>;
    virtual ~IKeyboardInjector() = default;
    virtual AsyncResult<KeyStates> press(ObjectId target_id, KeyboardKey key) = 0;
    virtual AsyncResult<KeyStates> release(ObjectId target_id, KeyboardKey key) = 0;
    virtual AsyncResult<KeyStates> press_and_release(ObjectId target_id, KeyboardKey key) = 0;
    virtual AsyncResult<void> press_and_release_each(ObjectId target_id, std::string keys) = 0;
};
} // namespace quite::core
