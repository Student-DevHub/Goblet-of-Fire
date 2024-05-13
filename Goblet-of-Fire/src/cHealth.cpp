#include "cHealth.hpp"
#include <iostream>

namespace GobletOfFire::ObjectComponent {
  void cHealth::create() { this->health_ = 100; }
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
    std::cerr << "Ouch!" << damage << " " << health_ << "\n";
    notify();
  }

  void cHealth::heal(double heal) {
    health_ += heal;
    health_ = health_ > kMaxHealth_ ? kMaxHealth_ : health_;
    notify();
  }

  double cHealth::kMaxHealth_ = 100.0;
}