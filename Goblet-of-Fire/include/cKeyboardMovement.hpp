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
    
  private:
    void whileInAir();
    void whileOnGround();

    std::weak_ptr<iObject> owner_;
    std::weak_ptr<cPhysics> physics_;
    std::weak_ptr<cAnimation> animation_;
    std::shared_ptr<Input::InputManager> input_;

    /*
    * 1. Jump
    * 2. Left
    * 3. Right
    * 4. Attack
    */

    std::map<uint32_t, Input::InputManager::Key> key_binds_;

  };
}

#endif // !C_KEYBOARD_MOVEMENT_HPP
