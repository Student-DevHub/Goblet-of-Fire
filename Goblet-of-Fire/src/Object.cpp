#include "Object.hpp"

namespace GobletOfFire {
  namespace ObjectComponent {
    void Object::create() {
      auto create_components = [](const std::pair<iComponent::Type, std::shared_ptr<iComponent>>& pair) {
                          pair.second->create();
                        };

      std::for_each(components_.begin(), components_.end(), create_components);
      destroyed_.store(false);
    }

    void Object::destroy() {
      auto destroy_components = [](const std::pair<iComponent::Type, std::shared_ptr<iComponent>>& pair) {
        pair.second->destroy();
        };

      std::for_each(components_.begin(), components_.end(), destroy_components);

      destroyed_.store(true);
    }

    void Object::activate() {
      auto activate_components = [](const std::pair<iComponent::Type, std::shared_ptr<iComponent>>& pair) {
        pair.second->activate();
        };

      std::for_each(components_.begin(), components_.end(), activate_components);
    }

    void Object::deActivate() {
      auto deActivate_components = [](const std::pair<iComponent::Type, std::shared_ptr<iComponent>>& pair) {
        pair.second->deActivate();
        };

      std::for_each(components_.begin(), components_.end(), deActivate_components);
    }

    void Object::update(const iComponent::Type type, const Utilities::Time::duration dt) {
      auto component = getComponent(type);
      if (component) {
        component->update(dt);
      }
    }

    void Object::render(Graphics::buffer& destination) const {
      auto sprite = getComponent(iComponent::Type::kSprite);
      if (sprite) {
        sprite->render(destination);
      }
    }

    void Object::addComponent(const iComponent::Type type, const std::shared_ptr<iComponent>& component) {
      components_.insert(std::make_pair(type, component));
    }

    void Object::removeComponent(const iComponent::Type type) {
      auto it = getComponent_i(type);
      if (it != components_.end()) {
        components_.erase(it);
      }
    }

    std::shared_ptr<iComponent> Object::getComponent(const iComponent::Type type) const {
      auto it = getComponent_i(type);
      if (it != components_.end()) {
        return it->second;
      }
      return nullptr;
    }

    bool Object::isDestroyed() const {
      return destroyed_.load();
    }

    Object::iterator Object::getComponent_i(iComponent::Type type) const {
      return components_.find(type);
    }

  }
}