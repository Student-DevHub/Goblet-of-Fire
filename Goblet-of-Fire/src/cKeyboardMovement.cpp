#include "cKeyboardMovement.hpp"

namespace GobletOfFire::ObjectComponent {
  void cKeyboardMovement::destroy() {}
  void cKeyboardMovement::activate() {}
  void cKeyboardMovement::deActivate() {}
  void cKeyboardMovement::render(Graphics::buffer&) {}

  cKeyboardMovement::cKeyboardMovement(std::shared_ptr<iObject> owner, std::shared_ptr<Input::InputManager> input, 
    std::shared_ptr<iObject> opponent
    )
    : owner_(owner), input_(input), isAttack(false), opponent_(opponent), attack_duration_(Utilities::Time::duration(0)) {
    key_binds_[1] = Input::InputManager::Key::kW;
    key_binds_[2] = Input::InputManager::Key::kA;
    key_binds_[3] = Input::InputManager::Key::kD;
    key_binds_[4] = Input::InputManager::Key::kF;
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

    checkForAttack(dt);
    
    if(!isAttack && velocity.y != 0) {
      whileInAir();
    }
    else if(!isAttack) {
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

  void cKeyboardMovement::checkForAttack(Utilities::Time::duration dt)
  {
    static const Utilities::Time::duration attack_duration = Utilities::Time::duration(350);
    if (!isAttack && input_->isKeyPressed(key_binds_[4])) {
      isAttack = true;
      animation_.lock()->setAnimationState(6);
      attack_duration_ = Utilities::Time::duration(0);

      auto dir = animation_.lock()->getDirection();
      
      auto collider = std::dynamic_pointer_cast<cCollision>(owner_.lock()->getComponent(iComponent::Type::kCollision));
      auto collider_opp = std::dynamic_pointer_cast<cCollision>(opponent_.lock()->getComponent(iComponent::Type::kCollision));

      auto c = collider->getBoundingBox();
      auto c_opp = collider_opp->getBoundingBox();

      auto health = std::dynamic_pointer_cast<cHealth>(opponent_.lock()->getComponent(iComponent::Type::kHealth));

      if (dir == cAnimation::FacingDirection::kRight) {
        auto range = c.left + c.width + 45.f;
        if (c_opp.left > c.left && c_opp.left < range) {
          health->takeDamage(10.0);
        }
      }else {
        auto range = c.left - 60.f;
        if (c_opp.left + c_opp.width < c.left + c.width && c_opp.left > range) {
          health->takeDamage(10.0);
        }
      }
    }

    if (isAttack) {
      attack_duration_ += dt;
      if (attack_duration_ > attack_duration) {
        isAttack = false;
      }
    }

  }

}