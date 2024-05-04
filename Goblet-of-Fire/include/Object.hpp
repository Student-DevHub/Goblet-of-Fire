#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <atomic>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>
#include <algorithm>

#include "Utilities.hpp"
#include "Graphics.hpp"
#include "ObjectComponents.hpp"

namespace GobletOfFire {
  namespace ObjectComponent {
    class Object {
    public:
      void create();
      void destroy();

      void activate();
      void deActivate();

      void update(const iComponent::Type, const Utilities::Time::duration) const;
      void render(Graphics::buffer&) const;

      void addComponent(const iComponent::Type, const std::shared_ptr<iComponent>&);
      void removeComponent(const iComponent::Type);
      std::shared_ptr<iComponent> getComponent(const iComponent::Type) const;

      bool isDestroyed() const;

    private:
      using iterator = std::unordered_map<iComponent::Type, std::shared_ptr<iComponent>>::const_iterator;
      iterator getComponent_i(iComponent::Type) const;

      std::unordered_map<iComponent::Type, std::shared_ptr<iComponent>> components_;
      std::atomic<bool> destroyed_;
    };
  }
}

#endif // !OBJECT_HPP
