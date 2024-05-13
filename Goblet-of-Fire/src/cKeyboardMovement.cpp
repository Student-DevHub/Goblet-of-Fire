#include "cKeyboardMovement.hpp"

namespace GobletOfFire::ObjectComponent {
  void cKeyboardMovement::destroy() {}
  void cKeyboardMovement::activate() {}
  void cKeyboardMovement::deActivate() {}
  void cKeyboardMovement::render(Graphics::buffer&) {}

  cKeyboardMovement::cKeyboardMovement(std::shared_ptr<iObject> owner, std::shared_ptr<Input::InputManager> input)
    : owner_(owner), input_(input) {
    key_binds_[1] = Input::InputManager::Key::kW;
    key_binds_[2] = Input::InputManager::Key::kA;
    key_binds_[3] = Input::InputManager::Key::kD;
  }

  void cKeyboardMovement::create() {
    if (owner_.expired()) {
      throw std::runtime_error("Owner of cKeyboardMovement is expired!");
    }

    if (!input_) {
      throw std::runtime_error("Input is nullptr (cKeyboardMovement)!");
    }
    {
      auto ptr1 = std::dynamic_pointer_cast<cPhysics>(owner_.lock()->getComponent(iComponent::Type::kPhysics));
      if (!ptr1)
        throw std::runtime_error("Pointer not casted to cTransform in cKeyboardMovement");

      physics_ = ptr1;
    }

    {
      auto ptr2 = std::dynamic_pointer_cast<cAnimation>(owner_.lock()->getComponent(iComponent::Type::kAnimation));
      if (!ptr2)
        throw std::runtime_error("Pointer not casted to cAnimation in cKeyboardMovement");

      animation_ = ptr2;
    }
  
  }


  void cKeyboardMovement::update(const Utilities::Time::duration dt) {
    auto velocity = physics_.lock()->getVelocity();
    auto acceleration = physics_.lock()->getAcceleration();

    if (velocity.y != 0) {
      whileInAir();
    }
    else {
      whileOnGround();
    }
  }

  void cKeyboardMovement::changeKeyBind(uint32_t id, Input::InputManager::Key key) {
    key_binds_[id] = key;
  }

  void cKeyboardMovement::whileInAir() {
    auto velocity = physics_.lock()->getVelocity();
    auto max_velocity = physics_.lock()->getMaxVelocity();

    if (input_->isKeyPressed(key_binds_[2])) {
      animation_.lock()->changeDirection(cAnimation::FacingDirection::kLeft);
      velocity.x = -1 * max_velocity.x;
    }
    else if (input_->isKeyPressed(key_binds_[3])) {
      animation_.lock()->changeDirection(cAnimation::FacingDirection::kRight);
      velocity.x = max_velocity.x;
    }
    else if ((!input_->isKeyHold(key_binds_[2])) && (!input_->isKeyHold(key_binds_[3]))) {
      velocity.x = 0;
    }

    if (velocity.y >= 0) {
      animation_.lock()->setAnimationState(5);
    }
    else {
      animation_.lock()->setAnimationState(3);
    }
    physics_.lock()->setVelocity(velocity);
  }

  void cKeyboardMovement::whileOnGround() {
    auto velocity = physics_.lock()->getVelocity();
    auto acceleration = physics_.lock()->getAcceleration();

    auto max_velocity = physics_.lock()->getMaxVelocity();

    if (input_->isKeyPressed(key_binds_[2])) {
      animation_.lock()->setAnimationState(2);
      animation_.lock()->changeDirection(cAnimation::FacingDirection::kLeft);
      velocity.x = -1 * max_velocity.x;
    }
    else if (input_->isKeyPressed(key_binds_[3])) {
      animation_.lock()->setAnimationState(2);
      animation_.lock()->changeDirection(cAnimation::FacingDirection::kRight);
      velocity.x = max_velocity.x;
    }
    else if ((!input_->isKeyHold(key_binds_[2])) && (!input_->isKeyHold(key_binds_[3]))) {
      animation_.lock()->setAnimationState(4);
      velocity.x = 0;
    }
    if (input_->isKeyPressed(key_binds_[1])) {
      velocity.y = -1 * max_velocity.y;
      acceleration.y = physics_.lock()->getGravity();
      animation_.lock()->setAnimationState(3);
    }

    physics_.lock()->setAcceleration(acceleration);
    physics_.lock()->setVelocity(velocity);
  }

}