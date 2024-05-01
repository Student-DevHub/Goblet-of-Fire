#pragma once
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "Utilities.hpp"
#include "Graphics.hpp"
#include "Scenes.hpp"

namespace GobletOfFire {
  namespace Scenes {
    class Component {
    public:
      enum class Type {
        kTransform,
        kMovement,
        kSprite,
        kRender,
        kAnimation,
        kCollision
      };

      virtual void create() = 0;
      virtual void destroy() = 0;

      virtual void activate() = 0;
      virtual void deActivate() = 0;

      virtual void update(const Utilities::Time::duration) = 0;
      virtual void render(std::shared_ptr<Graphics::buffer>) = 0;
    };
  }
}
#endif // !COMPONENT_HPP
