#pragma once
#ifndef I_OBJECT_HPP
#define I_OBJECT_HPP

#include <Graphics.hpp>
#include <Utilities.hpp>
#include <ObjectComponents.hpp>

namespace GobletOfFire {
  namespace ObjectComponent {
    class iObject {
    public:
      uint32_t kLayer_;

      virtual void create() = 0;
      virtual void destroy() = 0;

      virtual void activate() = 0;
      virtual void deActivate() = 0;

      virtual void update(const iComponent::Type, const Utilities::Time::duration) = 0;
      virtual void render(Graphics::buffer&) const = 0;

      virtual void addComponent(const iComponent::Type, const std::shared_ptr<iComponent>&) = 0;
      virtual void removeComponent(const iComponent::Type) = 0;
      virtual std::shared_ptr<iComponent> getComponent(const iComponent::Type) const = 0;

      virtual bool isDestroyed() const = 0;
    };
  }
}

#endif // !I_OBJECT_HPP
