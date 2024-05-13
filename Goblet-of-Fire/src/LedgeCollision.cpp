#include <LedgeCollision.hpp>

namespace GobletOfFire::ObjectComponent {
  LedgeCollision::LedgeCollision(std::shared_ptr<iObject> owner, std::shared_ptr<Physics::QuadTree> quadtree, const CollisionBox& box)
    : cCollision(owner, quadtree, box, Layer::kLedgeLayer) {}
  void LedgeCollision::resolveCollision(std::shared_ptr<cCollision>)
  {
  }
  void LedgeCollision::checkWindowBounds()
  {
  }
}