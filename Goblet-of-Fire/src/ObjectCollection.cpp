#include "ObjectCollection.hpp"

namespace GobletOfFire {
  namespace ObjectComponent {
    void ObjectCollection::add(const std::shared_ptr<iObject>& object) {
      new_objects_.push_back(object);
    }

    void ObjectCollection::render(Graphics::buffer& destination) {
      auto render_func = [&destination](const std::shared_ptr<iObject>& ptr) {
        ptr->render(destination);
        };

      std::for_each(object_collection_.begin(), object_collection_.end(), render_func);
    }

    void ObjectCollection::update(const iComponent::Type type, const Utilities::Time::duration duration) {
      auto update_component = [&type, &duration](const std::shared_ptr<iObject>& ptr) {
        ptr->update(type, duration);
        };

      std::for_each(object_collection_.begin(), object_collection_.end(), update_component);
    }

    void ObjectCollection::processAddition() {
      std::for_each(new_objects_.begin(), new_objects_.end(), [&](const std::shared_ptr<iObject> ptr) {
        ptr->create();
        ptr->activate();
        object_collection_.push_back(ptr);
        });

      new_objects_.clear();
    }

    void ObjectCollection::processRemovals() {
      auto it = std::remove_if(object_collection_.begin(), object_collection_.end(), [&](const std::shared_ptr<iObject> ptr) {
        return ptr->isDestroyed();
        });

      object_collection_.erase(it, object_collection_.end());
    }


  }
}