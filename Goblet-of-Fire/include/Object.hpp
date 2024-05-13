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
    class Object : public iObject {
    public:

      Object(uint32_t layer) { kLayer_ = layer; }
      Object() { kLayer_ = 0u; }

      void create() override;
      void destroy() override;

      void activate() override;
      void deActivate() override;

      void update(const iComponent::Type, const Utilities::Time::duration) override;
      void render(Graphics::buffer&) const override;

      void addComponent(const iComponent::Type, const std::shared_ptr<iComponent>&) override;
      void removeComponent(const iComponent::Type) override;
      std::shared_ptr<iComponent> getComponent(const iComponent::Type) const override;

      bool isDestroyed() const override;

    private:
      using iterator = std::unordered_map<iComponent::Type, std::shared_ptr<iComponent>>::const_iterator;
      iterator getComponent_i(iComponent::Type) const;

      std::unordered_map<iComponent::Type, std::shared_ptr<iComponent>> components_;
      std::atomic<bool> destroyed_;
    };
  }
}

#endif // !OBJECT_HPP
