#pragma once
#ifndef C_KEYBOARD_MOVEMENT_HPP
#define C_KEYBOARD_MOVEMENT_HPP

#include <functional>
#include <cstdint>
#include <memory>
#include <map>

#include <ObjectComponents.hpp>
#include <Utilities.hpp>
#include <Physics.hpp>
#include <Input.hpp>

namespace GobletOfFire::ObjectComponent {
  class cKeyboardMovement : public iComponent {
  public:
    cKeyboardMovement(std::shared_ptr<iObject>, std::shared_ptr<Input::InputManager>);

    virtual void create() override;
    virtual void destroy() override;

    virtual void activate() override;
    virtual void deActivate() override;

    virtual void update(const Utilities::Time::duration) override;
    virtual void render(Graphics::buffer&) override;

    void changeKeyBind(uint32_t, Input::InputManager::Key);
    void changeMovementSpeed(float, float);
    void changeMovementSpeed(Physics::point2<float>);
    
  private:
    std::weak_ptr<iObject> owner_;
    std::shared_ptr<cTransform> transform_;
    std::shared_ptr<cAnimation> animation_;
    std::shared_ptr<Input::InputManager> input_;

    std::map<uint32_t, Input::InputManager::Key> key_binds_;
    std::map<uint32_t, std::function<void()>> call_backs_;

    Physics::point2<float> speed_;
    Physics::point2<float> current_move_;
  };
}

#endif // !C_KEYBOARD_MOVEMENT_HPP
