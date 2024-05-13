#pragma once

#include <cCollision.hpp>

namespace GobletOfFire::ObjectComponent {
  class PlayerCollision : public cCollision {
  public:
    PlayerCollision(std::shared_ptr<iObject>,
      std::shared_ptr<Physics::QuadTree>,
      const CollisionBox&);

  protected:
    virtual void resolveCollision(std::shared_ptr<cCollision>) override;
    virtual void checkWindowBounds() override;

    void whenAboveLedge(Physics::worldBox<float>, Physics::worldBox<float>);
    void whenBelowLedge(Physics::worldBox<float>, Physics::worldBox<float>);
      
    float calculateLedgeCoverage(Physics::point2<float>, Physics::point2<float>);
  };
}