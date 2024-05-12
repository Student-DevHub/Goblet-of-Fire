#pragma once
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Utilities.hpp"
#include "Graphics.hpp"
#include "Scene.hpp"

namespace GobletOfFire {
  namespace ObjectComponent {

    class iComponent {
    public:
      enum class Type {
        kTransform,
        kMovement,
        kAnimation,
        kSprite,
        kPhysics,
        kCollision,
        kAttack,
        kHealth
      };

      virtual void create() = 0;
      virtual void destroy() = 0;

      virtual void activate() = 0;
      virtual void deActivate() = 0;

      virtual void update(const Utilities::Time::duration) = 0; //duration is in milliseconds
      virtual void render(Graphics::buffer&) = 0;
    };

  }
}
#endif // !COMPONENT_HPP
