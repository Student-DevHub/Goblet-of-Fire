#pragma once
#include <cCollision.hpp>

namespace GobletOfFire::ObjectComponent {
  class LedgeCollision : public cCollision {
  public:
    LedgeCollision(std::shared_ptr<iObject>,
      std::shared_ptr<Physics::QuadTree>,
      const CollisionBox&);

  protected:
    virtual void resolveCollision(std::shared_ptr<cCollision>) override;
    virtual void checkWindowBounds() override;
  };
}