#include "cTransform.hpp"

namespace GobletOfFire::ObjectComponent {
  cTransform::cTransform(uint32_t x, uint32_t y)
    : point_(Physics::point2<uint32_t>(x, y)) {}

  void cTransform::create() {}
  void cTransform::destroy() {}

  void cTransform::activate() {}
  void cTransform::deActivate() {}
  void cTransform::update(const Utilities::Time::duration) {}
  void cTransform::render(Graphics::buffer&) {}

  void cTransform::setPosition(uint32_t x, uint32_t y) {
    point_.x = x;
    point_.y = y;
  }
  void cTransform::setPosition(Physics::point2<uint32_t> point) {
    point_ = point;
  }

  Physics::point2<uint32_t> cTransform::getPoint() const {
    return point_;
  }
}