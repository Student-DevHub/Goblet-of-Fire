#pragma once
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <memory>
#include <atomic>
#include <cstdint>

#include "Utilities.hpp"
#include "Graphics.hpp"
#include "Scenes.hpp"

namespace GobletOfFire {
  namespace Scenes {
    class Object {
    public:
      void create();
      void destroy();

      void activate();
      void deActivate();

      void update(const Component::Type, const Utilities::Time::duration);
      void render(std::shared_ptr<Graphics::buffer>);

      void addComponent(const Component::Type, std::shared_ptr<Component> component);
      void removeComponent(const Component::Type);
      std::shared_ptr<Component> getComponent(const Component::Type);

      bool getDestroyed() const;

    private:
      std::unordered_map<Component::Type, std::shared_ptr<Component>> components_;
      std::atomic<bool> destroyed_;
    };
  }
}

#endif // !OBJECT_HPP
