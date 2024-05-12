#include "cPhysics.hpp"

namespace GobletOfFire::ObjectComponent {
  cPhysics::cPhysics(std::shared_ptr<iObject> owner,
    Physics::point2<float> max_velocity,
    float mass,
    float gravity)
    : owner_(owner), max_velocity_(max_velocity), mass_(mass),
    gravity_(gravity), velocity_({ 0.f,0.f }), 
    acceleration_({ 0.f, 0.f }) {}

  void cPhysics::create() {
    if (owner_.expired()) {
      throw std::runtime_error("Owner expired inside cPhysics");
    }

    auto ptr = std::dynamic_pointer_cast<cTransform>(owner_.lock()->getComponent(iComponent::Type::kTransform));

    if (!ptr) {
      throw std::runtime_error("Dynamic pointer cast failed in cPhysics");
    }

    transform_ = ptr;
  }

  void cPhysics::update(const Utilities::Time::duration dt) {
    float dt_ = static_cast<float>(dt.count()) / static_cast<float>(1000);

    velocity_.x = velocity_.x + acceleration_.x * dt_;
    velocity_.y = velocity_.y + acceleration_.y * dt_;

    auto dx = velocity_.x * dt_;
    auto dy = velocity_.y * dt_;

    Physics::point2<float> new_point{ dx + transform_.lock()->getPoint().x, dy + transform_.lock()->getPoint().y };
    transform_.lock()->setPosition(new_point);
  }

  void cPhysics::setVelocity(Physics::point2<float> velocity) {
    velocity_ = velocity;
  }

  Physics::point2<float> cPhysics::getVelocity() const {
    return velocity_;
  }

  Physics::point2<float> cPhysics::getMaxVelocity() const {
    return max_velocity_;
  }

  void cPhysics::setAcceleration(Physics::point2<float> acceleration) {
    acceleration_ = acceleration;
  }

  Physics::point2<float> cPhysics::getAcceleration() const {
    return acceleration_;
  }

  float cPhysics::getMass() const {
    return mass_;
  }
  float cPhysics::getGravity() const {
    return gravity_;
  }
  void cPhysics::setGravity(float g) {
    gravity_ = g;
  }
}