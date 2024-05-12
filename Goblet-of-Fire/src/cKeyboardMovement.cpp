#include "cKeyboardMovement.hpp"

namespace GobletOfFire::ObjectComponent {
  void cKeyboardMovement::destroy() {}
  void cKeyboardMovement::deActivate() {}
  void cKeyboardMovement::render(Graphics::buffer&) {}

  cKeyboardMovement::cKeyboardMovement(std::shared_ptr<iObject> owner, std::shared_ptr<Input::InputManager> input)
    : owner_(owner), input_(input), speed_(Physics::point2<float>(0.f, 0.f)) {}

  void cKeyboardMovement::create() {
    if (owner_.expired()) {
      throw std::runtime_error("Owner of cKeyboardMovement is expired!");
    }

    if (!input_) {
      throw std::runtime_error("Input is nullptr (cKeyboardMovement)!");
    }
    {
      auto ptr1 = std::dynamic_pointer_cast<cTransform>(owner_.lock()->getComponent(iComponent::Type::kTransform));
      if (!ptr1)
        throw std::runtime_error("Pointer not casted to cTransform in cKeyboardMovement");

      transform_ = ptr1;
    }

    {
      auto ptr2 = std::dynamic_pointer_cast<cAnimation>(owner_.lock()->getComponent(iComponent::Type::kAnimation));
      if (!ptr2)
        throw std::runtime_error("Pointer not casted to cAnimation in cKeyboardMovement");

      animation_ = ptr2;
    }
  
    {
      auto left = [&]() {
        current_move_.x = -1.0f * speed_.x;
        animation_->changeDirection(cAnimation::FacingDirection::kLeft);
        };
      auto right = [&]() {
        current_move_.x = 1.0f * speed_.x;
        animation_->changeDirection(cAnimation::FacingDirection::kRight);
        };
      auto up = [&]() {
        current_move_.y = -1.0f * speed_.y;
        };

      call_backs_.emplace(1, left);
      call_backs_.emplace(2, right);
      call_backs_.emplace(3, up);
    }
  
  }

  void cKeyboardMovement::activate() {
    if (!key_binds_.size()) {
      throw std::runtime_error("Keybinds are not defined! (cKeyboardMovement)");
    }
  }

  void cKeyboardMovement::update(const Utilities::Time::duration dt) {
    current_move_.x = 0.f;
    current_move_.y = 0.f;
  
    for (auto& key : key_binds_) {
      if (input_->isKeyPressed(key.second)) {
        auto it = call_backs_.find(key.first);

        if (it == call_backs_.end()) {
          throw std::runtime_error("Key bind incorrect...");
        }

        it->second();
      }
    }
    float dt_ = static_cast<float>(dt.count()) / static_cast<float>(1000);
    current_move_.x *= dt_;
    current_move_.y *= dt_;

    auto c_point = transform_->getPoint();

    transform_->setPosition(c_point.x + current_move_.x, c_point.y + current_move_.y);
    if (current_move_.x == 0 && current_move_.y == 0) {
      animation_->setAnimationState(4);
    }
    else {
      animation_->setAnimationState(2);
    }
  }

  void cKeyboardMovement::changeKeyBind(uint32_t id, Input::InputManager::Key key) {
    key_binds_[id] = key;
  }

  void cKeyboardMovement::changeMovementSpeed(float x, float y) {
    speed_.x = x;
    speed_.y = y;
  }

  void cKeyboardMovement::changeMovementSpeed(Physics::point2<float> speed) {
    changeMovementSpeed(speed.x, speed.y);
  }

}