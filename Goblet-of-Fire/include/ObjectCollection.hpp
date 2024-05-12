#pragma once
#ifndef OBJECT_COLLECTION_HPP
#define OBJECT_COLLECTION_HPP

#include <vector>
#include <map>
#include <algorithm>
#include <execution>

#include <ObjectComponents.hpp>
#include <Graphics.hpp>

namespace GobletOfFire {
  namespace ObjectComponent {
    class ObjectCollection {
    public:
      ObjectCollection() = default;

      void add(const std::shared_ptr<iObject>&);
      void update(const iComponent::Type, const Utilities::Time::duration);
      void render(Graphics::buffer&);

      void processAddition();
      void processRemovals();

    private:
      std::vector<std::shared_ptr<iObject>> new_objects_;
      std::map<uint32_t, std::unique_ptr<std::vector<std::shared_ptr<iObject>>>> object_collection_;

      /* for collision detection */
    };
  }
}


#endif // !OBJECT_COLLECTION_HPP
