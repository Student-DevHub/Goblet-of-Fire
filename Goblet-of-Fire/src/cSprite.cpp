#include "cSprite.hpp"

namespace GobletOfFire {
  namespace ObjectComponent {
    cSprite::cSprite(uint32_t sprite_id, std::shared_ptr<iObject> owner)
      : sprite_id_(sprite_id), owner_(owner), t_resource_manager_(nullptr) {}

    void cSprite::create() {
      t_resource_manager_ = Core::ResourceManager<Graphics::texture>::getInstance();
      texture_ = t_resource_manager_->load(sprite_id_);
      sprite_->setTexture(*texture_);
      
      if (owner_.expired()) {
        throw std::runtime_error("Owner of cSprite is expired!");
      }

      auto ptr = std::dynamic_pointer_cast<cTransform>(owner_.lock()->getComponent(iComponent::Type::kTransform));
      if (!ptr)
        throw std::runtime_error("Pointer not casted to cTransform in cSprite");

      transform_ = ptr;
    }

    void cSprite::destroy() {}
    void cSprite::activate() {}
    void cSprite::deActivate() {}
    void cSprite::update(const Utilities::Time::duration) {
      if (!transform_.expired()) {
        const auto& ptr = transform_.lock();
        sprite_->setPosition(static_cast<float>(ptr->getPoint().x), static_cast<float>(ptr->getPoint().y));
      }
    }

    void cSprite::render(Graphics::buffer& destination) {
      destination.draw(*sprite_);
    }

    void cSprite::setTextureRect(Physics::point2<int32_t> origin, Physics::point2<int32_t> size) {
      spriteRect rectangle(origin, size);
      sprite_->setTextureRect(rectangle);
    }
  }
}