#pragma once
#ifndef C_COLLISION_HPP
#define C_COLLISION_HPP

#include <memory>

#include <ObjectComponents.hpp>
#include <QuadTree.hpp>

namespace GobletOfFire::ObjectComponent {
  class cCollision : public iComponent,
    public std::enable_shared_from_this<cCollision> {
  public:

    enum class Layer : uint32_t {
      kPlayerLayer = 1 << 0,
      kProjectileLayer = 1 << 1,
      kLedgeLayer = 1 << 2
    };

    struct CollisionBox {
      Physics::point2<float> offset_;
      Physics::point2<float> d_;
    };

    cCollision(std::shared_ptr<iObject>,
      std::shared_ptr<Physics::QuadTree>,
      const CollisionBox&, const Layer);

    virtual void create() override;
    virtual void destroy() override;

    virtual void activate() override;
    virtual void deActivate() override;

    virtual void update(const Utilities::Time::duration) override;
    virtual void render(Graphics::buffer&) override;

    Physics::worldBox<float> getBoundingBox() const;
    uint32_t getLayerMask() const;

  protected:
    virtual void resolveCollision(std::shared_ptr<cCollision>) = 0;
    virtual void checkWindowBounds() = 0;

    const CollisionBox collider_;

    std::weak_ptr<iObject> owner_;
    std::weak_ptr<cPhysics> physics_;
    std::weak_ptr<cTransform> transform_;

  private:
    uint32_t layer_mask_;

    static uint32_t getCollisionLayer(uint32_t);

    std::shared_ptr<Physics::QuadTree> quadtree_;
  };
}

#include <LedgeCollision.hpp>
#include <PlayerCollision.hpp>

#endif // !C_COLLISION_HPP