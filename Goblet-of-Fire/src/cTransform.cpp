#include "cTransform.hpp"

namespace GobletOfFire::ObjectComponent {
  cTransform::cTransform(float x, float y)
    : point_(Physics::point2<float>(x, y)) {}

  void cTransform::create() {}
  void cTransform::destroy() {}

  void cTransform::activate() {}
  void cTransform::deActivate() {}
  void cTransform::update(const Utilities::Time::duration) {}
  void cTransform::render(Graphics::buffer&) {}

  void cTransform::setPosition(float x, float y) {
    point_.x = x;
    point_.y = y;
  }
  void cTransform::setPosition(Physics::point2<float> point) {
    point_ = point;
  }

  Physics::point2<float> cTransform::getPoint() const {
    return point_;
  }
}