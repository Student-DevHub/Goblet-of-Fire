#pragma once
#ifndef OBJECT_COLLECTION_HPP
#define OBJECT_COLLECTION_HPP

#include <vector>
#include <algorithm>
#include <execution>

#include <ObjectComponents.hpp>
#include <Graphics.hpp>

namespace GobletOfFire {
  namespace ObjectComponent {
    class ObjectCollection {
    public:
      ObjectCollection() = default;


      void add(const std::shared_ptr<Object>&);
      void update(const iComponent::Type, const Utilities::Time::duration);
      void render(Graphics::buffer&);

      void processAddition();
      void processRemovals();

    private:

    };
  }
}


#endif // !OBJECT_COLLECTION_HPP
