#include <cCollision.hpp>
#include <iostream>

namespace GobletOfFire::ObjectComponent {
  cCollision::cCollision(std::shared_ptr<iObject> owner,
    std::shared_ptr<Physics::QuadTree> quadtree,
    const CollisionBox& collider, const Layer layer)
    : owner_(owner), quadtree_(quadtree), collider_(collider), layer_mask_(static_cast<uint32_t>(layer)) {}

  void cCollision::create() {
    if (owner_.expired()) {
      throw std::runtime_error("Owner is expired");
    }
    if (!quadtree_) {
      throw std::runtime_error("QuadTree is nullptr");
    }


    auto tr = std::dynamic_pointer_cast<cTransform>(owner_.lock()->getComponent(iComponent::Type::kTransform));
    if (!tr) {
      throw std::runtime_error("Owner doesn't have transform component");
    }
    transform_ = tr;

    auto ph = std::dynamic_pointer_cast<cPhysics>(owner_.lock()->getComponent(iComponent::Type::kPhysics));
    physics_ = ph;

    quadtree_->insert(shared_from_this());
  }
  void cCollision::destroy() {}
  void cCollision::activate() {}
  void cCollision::deActivate() {}

  void cCollision::update(const Utilities::Time::duration) {
    checkWindowBounds();

    auto colliders = quadtree_->getPotentialColliders(getBoundingBox());
    auto l = getCollisionLayer(getLayerMask());
    for (auto& collider : colliders) {
      if (l & collider->getLayerMask()) {
        resolveCollision(collider);
      }
    }
  }

  void cCollision::render(Graphics::buffer&) {}

  Physics::worldBox<float> cCollision::getBoundingBox() const {
    auto x = transform_.lock()->getPoint().x + collider_.offset_.x;
    auto y = transform_.lock()->getPoint().y + collider_.offset_.y;
    auto dx = collider_.d_.x;
    auto dy = collider_.d_.y;

    Physics::worldBox<float> rect(x, y, dx, dy);
    return rect;
  }
  uint32_t cCollision::getLayerMask() const {
    return layer_mask_;
  }

  uint32_t cCollision::getCollisionLayer(uint32_t layer_mask) {
    switch (layer_mask)
    {
    case static_cast<uint32_t>(Layer::kPlayerLayer):
      return static_cast<uint32_t>(Layer::kLedgeLayer);
    case static_cast<uint32_t>(Layer::kLedgeLayer):
      return 0u;
    case static_cast<uint32_t>(Layer::kProjectileLayer):
      return static_cast<uint32_t>(Layer::kLedgeLayer) |
        static_cast<uint32_t>(Layer::kPlayerLayer);
    default:
      return 0u;
    }
  }
}