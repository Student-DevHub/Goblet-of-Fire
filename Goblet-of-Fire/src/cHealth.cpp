#include "cHealth.hpp"

namespace GobletOfFire::ObjectComponent {
  void cHealth::create() {}
  void cHealth::destroy() {}
  void cHealth::activate() {}
  void cHealth::deActivate() {}
  void cHealth::update(const Utilities::Time::duration) {}
  void cHealth::render(Graphics::buffer&) {}

  double cHealth::getHealth() const {
    return health_;
  }

  void cHealth::takeDamage(double damage) {
    health_ -= damage;
    notify();
  }

  void cHealth::heal(double heal) {
    health_ += heal;
    health_ = health_ > kMaxHealth_ ? kMaxHealth_ : health_;
    notify();
  }

  double cHealth::kMaxHealth_ = 100.0;
}